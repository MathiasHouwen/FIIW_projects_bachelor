from typing import Callable, Optional, Any

from matplotlib import pyplot as plt

from src.processing import boxes_with_ssim
from src.utils.images_io import *
from src.utils.preprocesing import fourier_transform, magnitude_transform, gaussian_filter, inverse_fourier_transform, \
    remove_periodische_ruis

BASE_PATH = './../images'
PROCESS_PARAMS = {
    'test_1': {},
    'test_4': {
        '01': {'notch': (540, 140)},
        '05': {'notch': (540, 140)}
    }
}


# def removenoise_test_4():
#     # img = load_as_gray('./../images/test_1/input/01_missing_hole_01.jpg')
#     # cv2.imshow('Grayscale', img)
#     img = cv2.imread('./../images/test_4/input/01_short_01.jpg', cv2.IMREAD_GRAYSCALE)
#     fshift = fourier_transform(img)
#     # Compute magnitude spectrum for visualization
#     magnitude = magnitude_transform(fshift)
#     # Create Gaussian notch filter
#     gaussian_mask = gaussian_filter(img, (540, 140))
#     fshift_filtered = fshift * gaussian_mask
#     filtered_magnitude = magnitude_transform(fshift_filtered)
#     img_filtered = inverse_fourier_transform(fshift_filtered)
#
#     # Normalize images for visualization
#     magnitude_norm = cv2.normalize(magnitude, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
#     filtered_magnitude_norm = cv2.normalize(filtered_magnitude, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
#     img_filtered_norm = cv2.normalize(img_filtered, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
#     mask_overlay = magnitude_norm.copy()
#     mask_overlay[gaussian_mask == 0] = 255  # Highlight masked regions
#     cv2.imshow('filtered', img_filtered_norm)
#     cv2.imshow('raw', img)
#     plt.figure(figsize=(10, 8))
#
#     plt.subplot(2, 1, 1)
#     plt.imshow(magnitude_norm, cmap='gray')
#     plt.title("Original Magnitude Spectrum")
#
#     plt.subplot(2, 1, 2)
#     plt.imshow(filtered_magnitude_norm, cmap='gray')
#     plt.title("Filtered Magnitude Spectrum")
#
#     plt.tight_layout()
#     plt.show()

def handle_test_1(test:MatLike, template:MatLike) -> MatLike:
    return boxes_with_ssim(test, template)

def handle_test_4(test:MatLike, template:MatLike, params:dict) -> MatLike:
    filtered = remove_periodische_ruis(test, params['notch'])
    return boxes_with_ssim(filtered, template)


def do(test_dir_name:str, process:Callable[..., MatLike], gray=False):
    folder = ImageFolder(BASE_PATH, test_dir_name, gray)
    folder.clean_and_make_out_folder()
    for image_pair in folder.images:
        params = PROCESS_PARAMS[test_dir_name].get(image_pair.pcb_id)
        out_img = process(image_pair.test, image_pair.template, params) if params else process(image_pair.test,image_pair.template)
        folder.write_out_image(out_img, image_pair)


def main():
    # removenoise_test_4()

    # do('test_1', handle_test_1, True)
    do('test_4', handle_test_4, True)

if __name__ == '__main__':
    main()