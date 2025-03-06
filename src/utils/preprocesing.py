import cv2
import numpy as np
from cv2.typing import MatLike


def magnitude_transform(fshift):
    return 20 * np.log1p(np.abs(fshift))


def fourier_transform(img: MatLike):
    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    return fshift


def gaussian_filter(img: MatLike, notch_offset, sigma = 100):
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

    gaussian_mask = apply_gaussian_notch(gaussian_mask, center[1] + notch_offset[0], center[0] + notch_offset[1], sigma)
    gaussian_mask = apply_gaussian_notch(gaussian_mask, center[1] - notch_offset[0], center[0] - notch_offset[1], sigma)
    return gaussian_mask


def low_pass_filter(img: MatLike, radius = 50):
    rows, cols = img.shape
    crow, ccol = rows // 2, cols // 2

    mask = np.zeros((rows, cols), np.uint8)
    cv2.circle(mask, (ccol, crow), radius, 1, -1)
    return mask


def inverse_fourier_transform(img):
    f_ishift = np.fft.ifftshift(img)
    image_filtered = np.fft.ifft2(f_ishift)
    image_filtered = np.abs(image_filtered)

    # image_filtered = cv2.normalize(image_filtered, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
    return image_filtered