import cv2




def draw_bounding_boxes(img, contours, min_defect_area=1, padding_indication_boxes=10, image_ignore_padding=20, box_merge_area=50, draw_padding=True):
    boxes = []
    height, width, _ = img.shape

    # Collect valid bounding boxes
    for contour in contours:
        if cv2.contourArea(contour) > min_defect_area:
            x, y, w, h = cv2.boundingRect(contour)
            boxes.append((x, y, x + w, y + h))  # Store (x1, y1, x2, y2)

    # Merge close boxes
    boxes = merge_boxes(boxes, box_merge_area)

    # Draw refined bounding boxes
    for x1, y1, x2, y2 in boxes:
        xs_in_range = _in_range(x1, width, image_ignore_padding) and _in_range(x2, width, image_ignore_padding)
        ys_in_range = _in_range(y1, height, image_ignore_padding) and _in_range(y2, height, image_ignore_padding)
        if xs_in_range and ys_in_range:
            cv2.rectangle(img, (x1 - padding_indication_boxes, y1 - padding_indication_boxes), (x2 + padding_indication_boxes, y2 + padding_indication_boxes), (0, 0, 255), 3)  # Red in BGR

    if draw_padding:
        cv2.rectangle(img, (image_ignore_padding, image_ignore_padding), (width-image_ignore_padding, height-image_ignore_padding), (255, 255, 0),3)

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

def _in_range(x, dimension, padding):
    return padding <= x <= dimension - padding