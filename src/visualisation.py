import random

import numpy as np
from matplotlib import pyplot as plt

from src import utils


def visualise_decoder_output(h_codes:np.ndarray, v_codes:np.ndarray, mask:np.ndarray, title:str):
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


def draw_random_matches(left_img, right_img, left_pts, right_pts, num_matches=50):
    combined = np.hstack((left_img, right_img))
    offset = left_img.shape[1]

    idx = random.sample(range(len(left_pts)), min(num_matches, len(left_pts)))
    sampled_pts1 = left_pts[idx]
    sampled_pts2 = right_pts[idx]

    plt.figure(figsize=(12, 6))
    plt.imshow(combined.astype(np.uint8))
    for p1, p2 in zip(sampled_pts1, sampled_pts2):
        x1, y1 = p1
        x2, y2 = p2
        color = np.random.rand(3,)
        plt.plot([x1, x2 + offset], [y1, y2],
                 color=color, linewidth=0.6, alpha=0.8)
        plt.scatter([x1, x2 + offset], [y1, y2],
                    color=color, s=5)
        plt.title("Random Sample of Matches")