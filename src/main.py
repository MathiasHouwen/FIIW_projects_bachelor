import cv2
from src.utils.preprocesing import *
from src.utils.postprocesing import *
import matplotlib.pyplot as plt
import numpy as np
from skimage.metrics import structural_similarity as ssim
import os
from src.utils.images_io import *

BASE_PATH = './../images'

folder = ImageFolder(BASE_PATH, 'test_1')



def removenoise_test_4():
    # img = load_as_gray('./../images/test_1/input/01_missing_hole_01.jpg')
    # cv2.imshow('Grayscale', img)

    img = cv2.imread('./../images/test_4/input/01_short_01.jpg', cv2.IMREAD_GRAYSCALE)
    fshift = fourier_transform(img)

    # Compute magnitude spectrum for visualization
    magnitude = magnitude_transform(fshift)

    # Create Gaussian notch filter
    gaussian_mask = gaussian_filter(img, (540, 140))

    fshift_filtered = fshift * gaussian_mask
    filtered_magnitude = magnitude_transform(fshift_filtered)
    img_filtered = inverse_fourier_transform(fshift_filtered)

    # Normalize images for visualization
    magnitude_norm = cv2.normalize(magnitude, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
    filtered_magnitude_norm = cv2.normalize(filtered_magnitude, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
    img_filtered_norm = cv2.normalize(img_filtered, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)

    mask_overlay = magnitude_norm.copy()
    mask_overlay[gaussian_mask == 0] = 255  # Highlight masked regions

    # cv2.imshow('filtered', img_filtered_norm)
    # cv2.imshow('raw', img)
    # plt.figure(figsize=(10, 8))
    #
    # plt.subplot(2, 1, 1)
    # plt.imshow(magnitude_norm, cmap='gray')
    # plt.title("Original Magnitude Spectrum")
    #
    # plt.subplot(2, 1, 2)
    # plt.imshow(filtered_magnitude_norm, cmap='gray')
    # plt.title("Filtered Magnitude Spectrum")
    #
    # plt.tight_layout()
    # plt.show()


def main():
    removenoise_test_4()

    # file paths
    template_path = "./../images/template_images/01.JPG"
    defect = "01_missing_hole_01.JPG"
    test_path = f"./../images/test_1/input/{defect}"
    output_path = "./../images/test_1/output"
    os.makedirs(output_path, exist_ok=True)
    output_path = os.path.join(output_path, defect)

    template = cv2.imread(template_path, cv2.IMREAD_GRAYSCALE)
    test = cv2.imread(test_path, cv2.IMREAD_GRAYSCALE)

    # Vind de defecten d.m.v. ssim
    score, diff = ssim(template, test, full=True)
    diff = (diff * 255).astype("uint8")
    _, thresh = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY_INV)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    imgbox = draw_bounding_boxes(test_path, contours, 1)
    cv2.imwrite(output_path, imgbox)

    # Display
    plt.imshow(imgbox)
    plt.title("Thresholded Defect Areas with Red Boxes")
    plt.axis("off")
    plt.show()
if __name__ == '__main__':
    main()