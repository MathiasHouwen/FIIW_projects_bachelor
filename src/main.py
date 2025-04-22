import time
from typing import List

import matplotlib.pyplot as plt

import utils
import numpy as np
import cv2
from codec import Encoder
from GrayCodeCodec import GrayCodeEncoder
from src.GrayCodeCodec import GrayCodeDecoder
from src.calibration import calibrate_camera_from_checkerboard, undistort_image
from src.codec import Decoder
from src.visualisation import visualise_decoder_output


def load_views(view_paths: List[str]) -> List[np.array]:
    return [utils.load_images(view) for view in view_paths]


def show_graycode_captures():
    views = [
        "../dataset/GrayCodes_HighRes/graycodes_view0.xml",
        "../dataset/GrayCodes_HighRes/graycodes_view1.xml",
    ]
    left_view, right_view = load_views(views)
    show_captures(left_view, right_view)


def show_captures(left_view: List[np.array], right_view: List[np.array]):
    window_size = (int(left_view[0].shape[1]/2), int(left_view[0].shape[0]/2))
    left_window_name = "Left view"
    right_window_name = "Right view"

    cv2.namedWindow(left_window_name, cv2.WINDOW_NORMAL)
    cv2.resizeWindow(left_window_name, width=window_size[0], height=window_size[1])
    cv2.namedWindow(right_window_name, cv2.WINDOW_NORMAL)
    cv2.resizeWindow(right_window_name, width=window_size[0], height=window_size[1])

    for image_left,  image_right in zip(left_view, right_view):
        cv2.imshow(left_window_name, image_left)
        cv2.imshow(right_window_name, image_right)

        key = cv2.waitKey(1000)
        if key == 27:
            break

    cv2.destroyAllWindows()


def show_graycode_patterns():
    encoder = GrayCodeEncoder(1080, 1920, 10)
    show_encoder_patterns(encoder)


def show_encoder_patterns(encoder: Encoder):
    window_name = "Pattern"
    cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)
    cv2.resizeWindow(window_name, encoder.cols // 2, encoder.rows // 2)

    for n in range(encoder.n):
        pattern = encoder.get_encoding_pattern(n)
        dummy = np.copy(pattern)
        pattern = cv2.resize(dummy, (encoder.cols, encoder.rows))

        cv2.imshow(window_name, pattern)
        key = cv2.waitKey(1000)
        if key == "27":
            break

    cv2.destroyAllWindows()


def show_pattern_decoded():
    encoder = GrayCodeEncoder(1080, 1920, 10)
    decoder = GrayCodeDecoder(encoder.cols, encoder.rows, 10)
    for n in range(encoder.n):
        pattern = encoder.get_encoding_pattern(n)
        pattern = cv2.resize(np.copy(pattern), (encoder.cols, encoder.rows))
        decoder.set_frame(n, pattern)

    h_dec, v_dec, mask_dec = decoder.decode_frames()
    visualise_decoder_output(h_dec, v_dec, mask_dec, "reference pattern")


def show_captures_decoded():
    info = {"w":1200, "h":800, "folder": "GrayCodes"}
    # info = {"w":4752, "h":3168, "folder": "GrayCodes_HighRes"}
    decoder = GrayCodeDecoder(info["w"], info["h"], 10)
    views = [f"../dataset/{info["folder"]}/graycodes_view0.xml",f"../dataset/{info["folder"]}/graycodes_view1.xml",]
    left_view, right_view = load_views(views)
    for n, view in enumerate(left_view[2:]): # splicing vanaf 2 want image 0 en 1 zijn full lit of full dark
        decoder.set_frame(n, view)
    h_dec, v_dec, mask_dec = decoder.decode_frames()
    visualise_decoder_output(h_dec, v_dec, mask_dec, "left captures")
    for n, view in enumerate(right_view[2:]):
        decoder.set_frame(n, view)
    h_dec, v_dec, mask_dec = decoder.decode_frames()
    visualise_decoder_output(h_dec, v_dec, mask_dec, "right captures")


def undistort(path:str, K, dist):
    image = cv2.imread(path)
    undistorted = undistort_image(image, K, dist)

    # Show result
    plt.figure()
    plt.imshow(image)
    plt.title("original")
    plt.figure()
    plt.imshow(undistorted)
    plt.title("undistorted")

if __name__ == "__main__":
    # show_pattern_decoded()
    # show_captures_decoded()
    # show_graycode_patterns()
    # show_graycode_captures()

    # Calibrate using checkerboard images
    ret, K, dist, rvecs, tvecs = calibrate_camera_from_checkerboard("../dataset/GrayCodes/chess/*.jpg")
    undistort("../dataset/GrayCodes/chess/00.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/01.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/02.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/03.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/04.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/05.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/06.jpg", K, dist)
    undistort("../dataset/GrayCodes/chess/07.jpg", K, dist)

    # Load and undistort an image

    # cv2.imshow("Original", image)
    # cv2.imshow("Undistorted", undistorted)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    plt.show()


