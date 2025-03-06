import cv2
from src.utils.preprocesing import *
import matplotlib.pyplot as plt
import numpy as np


def main():
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

    cv2.imshow('filtered', img_filtered_norm)
    cv2.imshow('raw', img)
    plt.figure(figsize=(10, 8))

    plt.subplot(2, 1, 1)
    plt.imshow(magnitude_norm, cmap='gray')
    plt.title("Original Magnitude Spectrum")

    plt.subplot(2, 1, 2)
    plt.imshow(filtered_magnitude_norm, cmap='gray')
    plt.title("Filtered Magnitude Spectrum")

    plt.tight_layout()
    plt.show()

    # fft = fourier_transform(img)
    #
    # # cv2.imshow('', img)
    # cv2.imshow('', fft)


    #fshift = fourier_transform(img)
    #mask = create_filter(img)
    #masked = fshift * mask
    #image_filtered = inverse_fourier_transform(masked)
    #cv2.imshow('lowpass', image_filtered)



    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
    # try:
    #     main()
    # except Exception as e:
    #     print(f"Oeijoe er is een foutje: {e}")