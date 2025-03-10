import cv2

def draw_bounding_boxes(test_path, contours, min_area = 50, pad=5):
    # Set minimum area to filter out small contours (adjust based on your needs)
    test_w_box = cv2.imread(test_path)
    # Draw red rectangles around significant contours
    for contour in contours:
        if cv2.contourArea(contour) > min_area:
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(test_w_box, (x-pad, y-pad), (x + w + pad, y + h + pad), (255, 0, 0), 3)  # Red in BGR

    return test_w_box