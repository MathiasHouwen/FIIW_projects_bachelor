import os
import cv2
import uuid

import numpy as np


def create_dataset(num_images: int, location: str):
    if not os.path.exists(os.path.join(location, "pose_a")):
        os.mkdir(os.path.join(location, "pose_a"))
    if not os.path.exists(os.path.join(location, "pose_b")):
        os.mkdir(os.path.join(location, "pose_b"))

    images_a = 0
    images_b = 0

    cap = cv2.VideoCapture(0)

    while images_a + images_b < num_images:
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)

        cv2.imshow("camera", frame)

        key = cv2.waitKey(1)

        filename = uuid.uuid4().hex

        if key == ord('a'):
            cv2.imwrite(os.path.join(location, "pose_a", f"{filename}.jpg"), frame)
            images_a += 1
            print(f"Image of pose a saved \t images_a: {images_a} \t images_b: {images_b} \t total: {images_a + images_b}")
        elif key == ord('b'):
            cv2.imwrite(os.path.join(location, "pose_b", f"{filename}.jpg"), frame)
            images_b += 1
            print(f"Image of pose b saved \t images_a: {images_a} \t images_b: {images_b} \t total: {images_a + images_b}")


def load_images(folder, image_size: tuple):
    class_names = [dir for dir in os.listdir(folder) if os.path.isdir(os.path.join(folder, dir))]

    images = []
    class_ids = []

    for class_id, class_name in enumerate(class_names):
        class_path = os.path.join(folder, class_name)

        for file in os.listdir(class_path):
            image = cv2.imread(os.path.join(class_path, file))
            image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            image = cv2.resize(image, image_size)

            images.append(image)
            class_ids.append(class_id)

    indices = np.arange(0, len(images))
    np.random.shuffle(indices)

    images = np.array(images)
    class_ids = np.array(class_ids)

    split_idx = int(0.9 * len(indices))

    return (images[indices[:split_idx]], class_ids[indices[:split_idx]]),\
        (images[indices[split_idx:]], class_ids[indices[split_idx:]])


if __name__ == "__main__":
    create_dataset(50, "./Data")