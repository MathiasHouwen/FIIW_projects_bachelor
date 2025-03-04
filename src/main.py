import cv2
from src.utils.preprocesing import *
import matplotlib.pyplot as plt
import numpy as np


def main():
    # img = load_as_gray('./../images/test_1/input/01_missing_hole_01.jpg')
    # cv2.imshow('Grayscale', img)

    img = cv2.imread('./../images/test_4/input/01_short_01.jpg', cv2.IMREAD_GRAYSCALE)

    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)

    # Compute magnitude spectrum for visualization
    magnitude = 20 * np.log1p(np.abs(fshift))

    # Create Gaussian notch filter
    rows, cols = img.shape
    center = (rows // 2, cols // 2)

    # Create an all-ones mask
    gaussian_mask = np.ones((rows, cols), np.float32)

    def apply_gaussian_notch(mask, center_x, center_y, sigma=10):
        """ Apply a smooth Gaussian attenuation at a specific frequency location. """
        x, y = np.meshgrid(np.arange(cols), np.arange(rows))
        gaussian = np.exp(-((x - center_x) ** 2 + (y - center_y) ** 2) / (2 * sigma ** 2))
        mask *= (1 - gaussian)  # Subtract Gaussian from 1 to create a notch
        return mask

    notch_offset = (540, 140)
    sigma = 100


    gaussian_mask = apply_gaussian_notch(gaussian_mask, center[1] + notch_offset[0], center[0] + notch_offset[1], sigma)
    gaussian_mask = apply_gaussian_notch(gaussian_mask, center[1] - notch_offset[0], center[0] - notch_offset[1], sigma)


    fshift_filtered = fshift * gaussian_mask
    filtered_magnitude = 20 * np.log1p(np.abs(fshift_filtered))

    f_ishift = np.fft.ifftshift(fshift_filtered)
    img_filtered = np.fft.ifft2(f_ishift)
    img_filtered = np.abs(img_filtered)

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