import cv2
from cv2.typing import MatLike
import numpy as np
from skimage.metrics import structural_similarity as ssim
from src.utils.postprocesing import draw_bounding_boxes
from src.utils.preprocesing import remove_periodische_ruis


def boxes_with_ssim(test:MatLike, template:MatLike) -> MatLike:
    # Vind de defecten d.m.v. ssim
    score, diff = ssim(template, test, full=True)
    diff = (diff * 255).astype("uint8")
    _, thresh = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY_INV)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return draw_bounding_boxes(test, contours)


def ssim_after_period_ruis(test:MatLike, template:MatLike):
    clean_img = remove_periodische_ruis(test)
    return boxes_with_ssim(clean_img, template)