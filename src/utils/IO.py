import os
import cv2
from cv2.typing import MatLike

def load_as_gray(image_path: str) -> MatLike:
    img = cv2.imread(image_path)
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

def read_input_images(base_dir: str, test_dir_name: str) -> list[tuple[str, MatLike]]:
    images = []
    for path in os.listdir(f"{base_dir}/{test_dir_name}/input"):
        img = cv2.imread(path)
        name = os.path.basename(path)
        images += (name, img)
    return images

def template_img_path(base_path: str, test_img_name: str):
    pcb_id = test_img_name[0:2]
    return f"{base_path}/template_images/{pcb_id}.jpg"