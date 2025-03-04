import cv2
from src.utils.IO import loadAsGray
from src.utils.preprocesing import *


def main():
    img = loadAsGray('./../images/test_1/input/01_missing_hole_01.jpg')
    cv2.imshow('Grayscale', img)

    #fshift = fourier_transform(img)
    #mask = create_filter(img)
    #masked = fshift * mask
    #image_filtered = inverse_fourier_transform(masked)
    #cv2.imshow('lowpass', image_filtered)



    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(f"Oeijoe er is een foutje: {e}")