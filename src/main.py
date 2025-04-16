from typing import List

import matplotlib.pyplot as plt

import utils
import numpy as np
import cv2
from codec import Encoder
from GrayCodeCodec import GrayCodeEncoder
from src.GrayCodeCodec import GrayCodeDecoder
from src.codec import Decoder


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

    decoder = GrayCodeDecoder(encoder.cols, encoder.rows, 10)

    for n in range(encoder.n):
        pattern = encoder.get_encoding_pattern(n)
        dummy = np.copy(pattern)
        pattern = cv2.resize(dummy, (encoder.cols, encoder.rows))
        decoder.set_frame(n, pattern)

        # cv2.imshow(window_name, pattern)
        # key = cv2.waitKey(1000)
        # if key == "27":
        #     break

    h_dec, v_dec, mask_dec = decoder.decode_frames()
    plt.figure()
    plt.subplot(1, 2, 1)
    plt.imshow(h_dec)
    plt.title("Horizontal graycode values\nof reference pattern")
    plt.subplot(1, 2, 2)
    plt.imshow(v_dec)
    plt.title("Vertical graycode values\nof reference pattern")
    plt.colorbar()

    plt.figure()
    false_color = utils.create_false_color(h_dec, v_dec, mask_dec)
    plt.imshow(false_color)
    plt.title("False Color of reference pattern")

    cv2.destroyAllWindows()


if __name__ == "__main__":
    # show_graycode_captures()
    show_graycode_patterns()
    plt.show()
