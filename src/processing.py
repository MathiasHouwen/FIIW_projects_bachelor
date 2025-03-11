import cv2
from cv2.typing import MatLike
import numpy as np
from matplotlib import pyplot as plt
from skimage.metrics import structural_similarity as ssim
from src.utils.postprocesing import draw_bounding_boxes
from src.utils.preprocesing import remove_periodische_ruis


def boxes_with_ssim(test:MatLike, template:MatLike, test_raw:MatLike, min_defect_area=1, thresh=50) -> MatLike:
    # Vind de defecten d.m.v. ssim
    score, diff = ssim(test, template, full=True)
    diff = (diff - diff.min()) / (diff.max() - diff.min())
    diff = (diff * 255).astype("uint8")
    plt.title('SSIM difference')
    plt.imshow(diff, cmap='turbo')
    plt.colorbar()
    plt.figure()
    plt.title('Below threshold')
    _, thresh = cv2.threshold(diff, thresh, 255, cv2.THRESH_BINARY_INV)
    plt.imshow(thresh)
    plt.show()
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return draw_bounding_boxes(test_raw, contours, min_defect_area)
