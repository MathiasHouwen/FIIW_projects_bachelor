import cv2
from cv2.typing import MatLike
import numpy as np
from matplotlib import pyplot as plt
from skimage.metrics import structural_similarity as ssim
from src.utils.postprocesing import draw_bounding_boxes

def detect_features(detector_name, img: MatLike):
    if detector_name == "SIFT":
        detector = cv2.SIFT_create()
    elif detector_name == "ORB":
        detector = cv2.ORB_create(nfeatures=500)
    elif detector_name == "AKAZE":
        detector = cv2.AKAZE_create()
    else:
        raise ValueError("Invalid detector name")
    keypoints, descriptors = detector.detectAndCompute(img, None)
    return keypoints, descriptors


def match_features(detector_name, descriptors1, descriptors2) -> list[cv2.DMatch]:
    # Use FLANN or BFMatcher for matching
    if detector_name == "SIFT" or detector_name == "AKAZE":
        index_params = {"algorithm":1, "trees":5}
        search_params = {"checks":50}
        matcher = cv2.FlannBasedMatcher(index_params, search_params)
    else:
        matcher = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=False)

    matches = matcher.knnMatch(descriptors1, descriptors2, k=2)

    # Apply Lowe's ratio test
    good_matches = []
    for m, n in matches:
        if m.distance < 0.6 * n.distance:
            good_matches.append(m)
    return good_matches

def undo_transform(keypoints1, keypoints2, matches:list[cv2.DMatch], template, test) -> MatLike:
    src_pts = np.float32([keypoints1[m.queryIdx].pt for m in matches]).reshape(-1, 1, 2)
    dst_pts = np.float32([keypoints2[m.trainIdx].pt for m in matches]).reshape(-1, 1, 2)

    homography, _ = cv2.findHomography(dst_pts, src_pts, cv2.RANSAC)
    # CORRECTIE TEST IMAGE (om te zien of de transform volledig undone is)
    h, w = template.shape[:2]
    corrected_image = cv2.warpPerspective(test, homography, (w, h), flags=cv2.INTER_LINEAR)
    # INVERSE-CORRECTIE TEMPLATE (dan kan de SSIM laten zien in het perspectief van de test image)
    h, w = test.shape[:2]
    inverse_corrected_template_image = cv2.warpPerspective(template, np.linalg.inv(homography), (w, h), flags=cv2.INTER_LINEAR)
    return corrected_image, inverse_corrected_template_image

def feature_matching_undo_transform(test:MatLike, template:MatLike, algorithm:str="SIFT", k:int=50):
    keypoints1, descriptors1 = detect_features(algorithm, template)
    keypoints2, descriptors2 = detect_features(algorithm, test)

    good_matches = match_features(algorithm, descriptors1, descriptors2)
    good_matches = sorted(good_matches, key=lambda x: x.distance)[:k]

    img_matches = cv2.drawMatches(template, keypoints1, test, keypoints2, good_matches, None,
                                  flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

    plt.figure(figsize=(16,9))
    plt.imshow(img_matches)
    plt.title(f"Feature Matching using {algorithm}")

    corrected_img, uncorrected_temp = undo_transform(keypoints1, keypoints2, good_matches, template, test)
    return corrected_img, uncorrected_temp


def boxes_with_ssim(test:MatLike, template:MatLike, test_raw:MatLike, min_defect_area=1, thresh=75, plot=True) -> MatLike:
    # Vind de defecten d.m.v. ssim

    score, diff = ssim(test, template, full=True)
    diff = (diff * 255).astype("uint8")

    # >>> VOOR TEST_5 EN 6 (werkt ook zonder, maar dit is cleaner):
    mask = (template > 0).astype(np.uint8) # mask voor waar (getransfromeerde) template niet 0 is. (rotatie geeft lege hoeken van 0)
    mask_eroded = cv2.erode(mask, np.ones((15, 15), np.uint8), iterations=4) # erosie: "verdikt" de rand van de mask. Anders is de rand van de geroteerde pcb zichtbaar in SSIM
    diff_masked = np.where(mask_eroded, diff, 255) # lege gebied 255 maken (255 = 100% simularity, 0% difference)
    # <<<
    _, thresh = cv2.threshold(diff_masked, thresh, 255, cv2.THRESH_BINARY_INV)
    if plot:
        plt.figure()
        plt.title('SSIM similarity')
        plt.imshow(diff_masked, cmap='turbo')
        plt.colorbar()
        plt.figure()
        plt.title('Below threshold')
        plt.imshow(thresh, cmap='turbo')
        plt.colorbar()
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return draw_bounding_boxes(test_raw, contours, min_defect_area)
