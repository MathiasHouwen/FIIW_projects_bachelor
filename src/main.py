from typing import Callable

from src.processing import *
from src.utils.images_io import *
from src.utils.preprocesing import *
from config import BASE_PATH, PROCESS_PARAMS

PLOT = False


def handle_raw(test:MatLike, template:MatLike, test_raw:MatLike) -> tuple[MatLike, MatLike]:
    return boxes_with_ssim(test, template, test_raw, plot=PLOT), test

def handle_periodic_noise(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> tuple[MatLike, MatLike]:
    filtered = remove_periodische_ruis(test, params['notch'])
    return boxes_with_ssim(filtered, template, test_raw, plot=PLOT), filtered

def handle_median_filter(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> tuple[MatLike, MatLike]:
    filtered_test = median(test)
    filtered_template = median(template)
    min_defect, thresh = params['min_defect_area'], params['thresh']
    return boxes_with_ssim(filtered_test, filtered_template, test_raw, min_defect_area=min_defect, thresh=thresh, plot=PLOT), filtered_test

def handle_gaussian_filter(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> tuple[MatLike, MatLike]:
    filtered_test = gaussian(test)
    filtered_template = gaussian(template)
    min_defect, thresh = params['min_defect_area'], params['thresh']
    return boxes_with_ssim(filtered_test, filtered_template, test_raw, min_defect_area=min_defect, thresh=thresh, plot=PLOT), filtered_test

def test5test(test:MatLike, template:MatLike, test_raw:MatLike):
    # Initialize SIFT detector
    detector_name = "SIFT"
    keypoints1, descriptors1 = detect_features(detector_name, template)
    keypoints2, descriptors2 = detect_features(detector_name, test)

    good_matches = match_features(detector_name, keypoints1, descriptors1, keypoints2, descriptors2)
    good_matches = sorted(good_matches, key=lambda x: x.distance)[:50]  # Show top 50 matches

    img_matches = cv2.drawMatches(template, keypoints1, test, keypoints2, good_matches, None,
                                  flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

    # Display the results
    plt.figure(figsize=(12, 6))
    plt.imshow(img_matches)
    plt.title(f"Feature Matching using {detector_name}")
    plt.axis("off")
    plt.show()

    print(f"Number of good matches found: {len(good_matches)}")
    return


def main():
    # do('test_1', handle_raw, True)
    # do('test_2', handle_gaussian_filter, True)
    # do('test_3', handle_median_filter, True)
    # do('test_4', handle_periodic_noise, True)
    do('test_5', test5test, True)

def do(test_dir_name:str, process:Callable[..., MatLike], gray=False):
    print(f"handling test_dir: {test_dir_name}")
    folder = ImageFolder(BASE_PATH, test_dir_name, gray)
    folder.clean_and_make_out_and_processed_folder()
    num_of_images = len(folder.images)
    for i, image_pair in enumerate(folder.images):
        params = PROCESS_PARAMS[test_dir_name].get(image_pair.pcb_id)
        out_img, proc_img = process(image_pair.test, image_pair.template, image_pair.test_raw, params) if params else process(image_pair.test,image_pair.template, image_pair.test_raw)
        folder.write_out_image(out_img, image_pair)
        folder.write_processed_image(proc_img, image_pair)
        print(f"  -> processed {i+1}/{num_of_images} images")

if __name__ == '__main__':
    main()