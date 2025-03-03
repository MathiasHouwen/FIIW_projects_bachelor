import cv2
import numpy as np
from cv2.typing import MatLike


def fourier_transform(img: MatLike):
    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    return fshift


def create_filter(img: MatLike, radius = 50):
    rows, cols = img.shape
    crow, ccol = rows // 2, cols // 2

    mask = np.zeros((rows, cols), np.uint8)
    cv2.circle(mask, (ccol, crow), radius, 1, -1)
    return mask


def inverse_fourier_transform(img: MatLike):
    f_ishift = np.fft.ifftshift(img)
    image_filtered = np.fft.ifft2(f_ishift)
    image_filtered = np.abs(image_filtered)

    image_filtered = cv2.normalize(image_filtered, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
    return image_filtered