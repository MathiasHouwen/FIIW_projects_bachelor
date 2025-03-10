from typing import Callable

from src.processing import boxes_with_ssim
from src.utils.images_io import *

BASE_PATH = './../images'


#
# def removenoise_test_4():
#     # img = load_as_gray('./../images/test_1/input/01_missing_hole_01.jpg')
#     # cv2.imshow('Grayscale', img)
#
#     img = cv2.imread('./../images/test_4/input/01_short_01.jpg', cv2.IMREAD_GRAYSCALE)
#     fshift = fourier_transform(img)
#
#     # Compute magnitude spectrum for visualization
#     magnitude = magnitude_transform(fshift)
#
#     # Create Gaussian notch filter
#     gaussian_mask = gaussian_filter(img, (540, 140))
#
#     fshift_filtered = fshift * gaussian_mask
#     filtered_magnitude = magnitude_transform(fshift_filtered)
#     img_filtered = inverse_fourier_transform(fshift_filtered)
#
#     # Normalize images for visualization
#     magnitude_norm = cv2.normalize(magnitude, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
#     filtered_magnitude_norm = cv2.normalize(filtered_magnitude, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
#     img_filtered_norm = cv2.normalize(img_filtered, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
#
#     mask_overlay = magnitude_norm.copy()
#     mask_overlay[gaussian_mask == 0] = 255  # Highlight masked regions
#
#     # cv2.imshow('filtered', img_filtered_norm)
#     # cv2.imshow('raw', img)
#     # plt.figure(figsize=(10, 8))
#     #
#     # plt.subplot(2, 1, 1)
#     # plt.imshow(magnitude_norm, cmap='gray')
#     # plt.title("Original Magnitude Spectrum")
#     #
#     # plt.subplot(2, 1, 2)
#     # plt.imshow(filtered_magnitude_norm, cmap='gray')
#     # plt.title("Filtered Magnitude Spectrum")
#     #
#     # plt.tight_layout()
#     # plt.show()



def do(test_dir_name:str, process:Callable[[MatLike, MatLike], MatLike], gray=False):
    folder = ImageFolder(BASE_PATH, test_dir_name, gray)
    folder.clean_and_make_out_folder()
    for image_pair in folder.images:
        out_img = process(image_pair.test, image_pair.template)
        folder.write_out_image(out_img, image_pair)


def main():
    # removenoise_test_4()

    do('test_1', boxes_with_ssim, True)

if __name__ == '__main__':
    main()