import cv2
from cv2.typing import MatLike

def loadAsGray(imagePath: str) -> MatLike:
    img = cv2.imread(imagePath)
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)