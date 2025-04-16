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