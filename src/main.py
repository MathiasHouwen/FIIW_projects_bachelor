import cv2
from src.utils.preprocesing import *
import matplotlib.pyplot as plt
import numpy as np
from skimage.metrics import structural_similarity as ssim

def test_4_removenoise():
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


def main():
    #test_4_removenoise()

    # Load images
    template_path = "./../images/template_images/01.JPG"  # Path to the correct PCB image
    test_path = "./../images/test_1/input/01_missing_hole_01.jpg"

    template = cv2.imread(template_path, cv2.IMREAD_GRAYSCALE)
    test = cv2.imread(test_path, cv2.IMREAD_GRAYSCALE)

    # Compute Structural Similarity Index (SSIM) and get the difference image
    score, diff = ssim(template, test, full=True)
    diff = (diff * 255).astype("uint8")

    # Threshold the difference image
    _, thresh = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY_INV)

    thresh_bgr = cv2.cvtColor(thresh, cv2.COLOR_GRAY2BGR)

    # Find contours in the thresholded image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Set minimum area to filter out small contours (adjust based on your needs)
    min_area = 1
    test_w_box = cv2.imread(test_path)
    # Draw red rectangles around significant contours
    for contour in contours:
        if cv2.contourArea(contour) > min_area:
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(test_w_box, (x, y), (x + w, y + h), (0, 0, 255), 2)  # Red in BGR

    # Convert BGR to RGB for correct display in Matplotlib
    imgbox = cv2.cvtColor(test_w_box, cv2.COLOR_BGR2RGB)

    # Display the result
    plt.imshow(imgbox)
    plt.title("Thresholded Defect Areas with Red Boxes")
    plt.axis("off")
    plt.show()

    # img = load_as_gray('./../images/test_1/input/01_missing_hole_01.jpg')
    # cv2.imshow('Grayscale', img)

    # fft = fourier_transform(img)
    #
    # # cv2.imshow('', img)
    # cv2.imshow('', fft)

    #fshift = fourier_transform(img)
    #mask = create_filter(img)
    #masked = fshift * mask
    #image_filtered = inverse_fourier_transform(masked)
    #cv2.imshow('lowpass', image_filtered)

    #cv2.waitKey(0)
    #cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
    # try:
    #     main()
    # except Exception as e:
    #     print(f"Oeijoe er is een foutje: {e}")