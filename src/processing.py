import cv2
from cv2.typing import MatLike
import numpy as np
from matplotlib import pyplot as plt
from skimage.metrics import structural_similarity as ssim
from src.utils.postprocesing import draw_bounding_boxes
from src.utils.preprocesing import remove_periodische_ruis

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


def match_features(detector_name, keypoints1, descriptors1, keypoints2, descriptors2):
    # Use FLANN or BFMatcher for matching
    if detector_name == "SIFT" or detector_name == "AKAZE":
        index_params = dict(algorithm=1, trees=5)
        search_params = dict(checks=50)
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


def boxes_with_ssim(test:MatLike, template:MatLike, test_raw:MatLike, min_defect_area=1, thresh=75, plot=True) -> MatLike:
    # Vind de defecten d.m.v. ssim
    score, diff = ssim(test, template, full=True)
    # diff = (diff - diff.min()) / (diff.max() - diff.min())
    diff = (diff * 255).astype("uint8")
    _, thresh = cv2.threshold(diff, thresh, 255, cv2.THRESH_BINARY_INV)

    if plot:
        plt.title('SSIM difference')
        plt.imshow(diff, cmap='turbo')
        plt.colorbar()
        plt.figure()
        plt.title('Below threshold')
        plt.imshow(thresh)
        plt.show()
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return draw_bounding_boxes(test_raw, contours, min_defect_area)
