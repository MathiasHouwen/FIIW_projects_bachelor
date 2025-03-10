import cv2
from cv2.typing import MatLike


def draw_bounding_boxes(img:MatLike, contours, min_area = 50, pad=5):
    # Set minimum area to filter out small contours (adjust based on your needs)
    # Draw red rectangles around significant contours
    for contour in contours:
        if cv2.contourArea(contour) > min_area:
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(img, (x-pad, y-pad), (x + w + pad, y + h + pad), (255, 0, 0), 3)  # Red in BGR

    return img