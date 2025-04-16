
from typing import List, Optional
import xml.etree.ElementTree as ET
import cv2
import numpy as np


def load_images(path: str) -> Optional[List[np.array]]:
    try:
        tree = ET.parse(path)
        if tree is None:
            return None
        images_node = tree.find("images")
        images = []
        for path in images_node.text.split("\n"):
            if path == "":
                continue
            image = cv2.imread(path)
            if image is None or image.size == 0:
                print(f"Failed to load {path}")
            else:
                images.append(image)

        return images
    except FileNotFoundError:
        print(f"{path} file not found")
        return None

def create_false_color(h_codes:np.ndarray, v_codes:np.ndarray, mask:np.ndarray):
    h_norm = (255 * (h_codes / h_codes.max())).astype(np.uint8)
    v_norm = (255 * (v_codes / v_codes.max())).astype(np.uint8)

    h_norm[mask > 0] = 0
    v_norm[mask > 0] = 0

    # Red = horizontal code, Green = vertical code, Blue = 0
    rgb = np.stack([h_norm, v_norm, np.zeros_like(h_norm)], axis=-1)
    return rgb