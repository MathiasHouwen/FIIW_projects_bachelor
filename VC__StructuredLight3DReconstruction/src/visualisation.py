import random

import cv2
import matplotlib
import numpy as np
from matplotlib import pyplot as plt

from src import utils


def visualise_and_save_decoder_output(h_codes:np.ndarray, v_codes:np.ndarray, mask:np.ndarray, title:str, output_folder:str):
    plt.figure()
    plt.subplot(1, 2, 1)
    plt.imshow(h_codes, cmap='turbo')
    plt.title(f"Horizontal graycode values\nof {title}")
    plt.subplot(1, 2, 2)
    plt.imshow(v_codes, cmap='turbo')
    plt.title(f"Vertical graycode values\nof {title}")
    plt.colorbar()

    plt.figure()
    false_color = utils.create_false_color(h_codes, v_codes, mask)
    plt.imshow(false_color)
    plt.title(f"False Color of {title}")
    cv2.imwrite(f"{output_folder}/false_color.jpg", false_color)


def draw_and_save_random_matches(left_img, right_img, left_pts, right_pts, output_folder:str, num_matches=100):
    combined = np.hstack((left_img, right_img))
    offset = left_img.shape[1]

    idx = random.sample(range(len(left_pts)), min(num_matches, len(left_pts)))
    sampled_pts1 = left_pts[idx]
    sampled_pts2 = right_pts[idx]

    plt.figure(figsize=(12, 6))
    plt.imshow(combined.astype(np.uint8), cmap='grey')
    for p1, p2 in zip(sampled_pts1, sampled_pts2):
        x1, y1 = p1
        x2, y2 = p2
        color = np.random.rand(3,)
        plt.plot([x1, x2 + offset], [y1, y2],
                 color=color, linewidth=0.6, alpha=0.8)
        plt.scatter([x1, x2 + offset], [y1, y2],
                    color=color, s=5)
        plt.title("Random Sample of Matches")

    plt.savefig(f"{output_folder}/plotted_matches.png")

def visualise_and_save_point_cloud(points_3d, pts, color_img, output_folder:str, downsample=False, view_angle=(-45, -30, -60)):
    x = np.clip(pts[:, 0].astype(int), 0, color_img.shape[1] - 1)
    y = np.clip(pts[:, 1].astype(int), 0, color_img.shape[0] - 1)
    colors = color_img[y, x] / 255.0  # int 0-255 to float 0-1

    if downsample:
        random_sample_indices = np.random.choice(points_3d.shape[0], size=10000, replace=False)
        points_3d = points_3d[random_sample_indices]
        colors = colors[random_sample_indices]

    matplotlib.use("TkAgg")  # force een echte window zodat de 3d interactive is want pycharm captured windows in de IDE
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(points_3d[:, 0], points_3d[:, 1], points_3d[:, 2], c=colors, s=0.1)
    ax.set_title("3D Point Cloud")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    el, az, rl = view_angle
    ax.view_init(elev=el, azim=az, roll=rl)
    plt.tight_layout()
    plt.savefig(f"{output_folder}/point_cloud.png")