import cv2
from cv2.typing import MatLike
import numpy as np
from skimage.metrics import structural_similarity as ssim

def boxes_with_ssim(test:MatLike, template:MatLike) -> MatLike:
    # Vind de defecten d.m.v. ssim
    score, diff = ssim(template, test, full=True)
    diff = (diff * 255).astype("uint8")
    _, thresh = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY_INV)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return draw_bounding_boxes(test, contours)

def draw_bounding_boxes(img, contours, min_defect_area=0, pad=10, box_merge_area=50):
    boxes = []

    # Collect valid bounding boxes
    for contour in contours:
        if cv2.contourArea(contour) > min_defect_area:
            x, y, w, h = cv2.boundingRect(contour)
            boxes.append((x, y, x + w, y + h))  # Store (x1, y1, x2, y2)

    # Merge close boxes
    boxes = merge_boxes(boxes, box_merge_area)

    # Draw refined bounding boxes
    for x1, y1, x2, y2 in boxes:
        cv2.rectangle(img, (x1 - pad, y1 - pad), (x2 + pad, y2 + pad), (255, 0, 0), 3)  # Red in BGR

    return img

def merge_boxes(boxes, merge_distance):
    merged_boxes = []

    while len(boxes) > 0:
        x1, y1, x2, y2 = boxes[0]  # Take first box
        boxes = boxes[1:]

        close_boxes = []
        for (xx1, yy1, xx2, yy2) in boxes:
            if (
                xx1 <= x2 + merge_distance and xx2 >= x1 - merge_distance and
                yy1 <= y2 + merge_distance and yy2 >= y1 - merge_distance
            ):
                # Expand the box
                x1, y1, x2, y2 = min(x1, xx1), min(y1, yy1), max(x2, xx2), max(y2, yy2)
                close_boxes.append((xx1, yy1, xx2, yy2))

        # Remove merged boxes
        boxes = [b for b in boxes if b not in close_boxes]

        merged_boxes.append((x1, y1, x2, y2))

    return merged_boxes
