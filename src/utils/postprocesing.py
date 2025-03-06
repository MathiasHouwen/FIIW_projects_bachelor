import cv2


def draw_bounding_boxes(test_path, contours, min_area = 50):
    # Set minimum area to filter out small contours (adjust based on your needs)
    test_w_box = cv2.imread(test_path)
    # Draw red rectangles around significant contours
    for contour in contours:
        if cv2.contourArea(contour) > min_area:
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(test_w_box, (x, y), (x + w, y + h), (0, 0, 255), 2)  # Red in BGR

    # Convert BGR to RGB for correct display in Matplotlib
    imgbox = cv2.cvtColor(test_w_box, cv2.COLOR_BGR2RGB)
    return imgbox