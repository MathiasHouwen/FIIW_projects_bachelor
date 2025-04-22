from typing import List

import matplotlib.pyplot as plt
import matplotlib


import utils
import numpy as np
import cv2
from codec import Encoder
from GrayCodeCodec import GrayCodeEncoder
from src.GrayCodeCodec import GrayCodeDecoder
from src.calibration import calibrate_camera_from_checkerboard, undistort_image
from src.matching import get_matches_for_essentialMat
from src.visualisation import visualise_decoder_output, draw_random_matches, visualise_point_cloud


def load_views(view_paths: List[str]) -> List[np.array]:
    return [utils.load_images(view) for view in view_paths]

def show_pattern_decoded():
    encoder = GrayCodeEncoder(1080, 1920, 10)
    decoder = GrayCodeDecoder(encoder.cols, encoder.rows, 10)
    for n in range(encoder.n):
        pattern = encoder.get_encoding_pattern(n)
        pattern = cv2.resize(np.copy(pattern), (encoder.cols, encoder.rows))
        decoder.set_frame(n, pattern)

    h_dec, v_dec, mask_dec = decoder.decode_frames()
    visualise_decoder_output(h_dec, v_dec, mask_dec, "reference pattern")


def decode_captures_and_match():
    info = {"w":1200, "h":800, "folder": "GrayCodes"}
    # info = {"w":4752, "h":3168, "folder": "GrayCodes_HighRes"}
    decoder = GrayCodeDecoder(info["w"], info["h"], 10)
    views = [f"../dataset/{info["folder"]}/graycodes_view0.xml",f"../dataset/{info["folder"]}/graycodes_view1.xml",]
    left_view, right_view = load_views(views)
    for n, view in enumerate(left_view[2:]): # splicing vanaf 2 want image 0 en 1 zijn full lit of full dark
        decoder.set_frame(n, view)
    h_dec_l, v_dec_l, mask_dec_l = decoder.decode_frames()
    visualise_decoder_output(h_dec_l, v_dec_l, mask_dec_l, "left captures")
    for n, view in enumerate(right_view[2:]):
        decoder.set_frame(n, view)
    h_dec_r, v_dec_r, mask_dec_r = decoder.decode_frames()
    visualise_decoder_output(h_dec_r, v_dec_r, mask_dec_r, "right captures")

    pts_l, pts_r = get_matches_for_essentialMat(h_dec_l, v_dec_l, mask_dec_l,
                                                h_dec_r, v_dec_r, mask_dec_r)

    draw_random_matches(left_view[0], right_view[0], pts_l, pts_r)
    return pts_l, pts_r, left_view[0], right_view[0]

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

    pts_l, pts_r, left_img, right_img = decode_captures_and_match()
    ret, K, dist, rvecs, tvecs = calibrate_camera_from_checkerboard("../dataset/GrayCodes/chess/*.jpg")

    # camera projection:
    E, mask = cv2.findEssentialMat(pts_l, pts_r, K, method=cv2.RANSAC, prob=0.999, threshold=1.0)
    _, R, T, mask_pose = cv2.recoverPose(E, pts_l, pts_r, K)

    # 2d points -> 3d:
    P_l = K @ np.hstack((np.eye(3), np.zeros((3, 1))))  # Left camera projection matrix
    P_r = K @ np.hstack((R, T))                         # Right camera projection matrix
    points_4d = cv2.triangulatePoints(P_l, P_r, pts_l.T, pts_r.T) # transpose zodat shape 2,N is ipv N,2
    points_3d = cv2.convertPointsFromHomogeneous(points_4d.T).reshape(-1, 3)

    # visualisation:
    visualise_point_cloud(points_3d, pts_l, left_img, downsample=False, view_angle=(-45, -30, -60))

    plt.show()