import cv2
import numpy as np
import glob

from matplotlib import pyplot as plt


def calibrate_camera_from_checkerboard(images_path_pattern: str, checkerboard_size = (9, 7), square_size=1.0):
    # Criteria for cornerSubPix
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    objp = np.zeros((checkerboard_size[0] * checkerboard_size[1], 3), np.float32)
    objp[:, :2] = np.mgrid[0:checkerboard_size[0], 0:checkerboard_size[1]].T.reshape(-1, 2)
    objp *= square_size

    objpoints = []  # 3D points in real world
    imgpoints = []  # 2D points in image

    image_files = glob.glob(images_path_pattern)
    print(f"Found {len(image_files)} images: {image_files}")
    for i, fname in enumerate(image_files):
        # if i > 15: continue
        image = cv2.imread(fname)
        if image is None:
            print(f"Failed to load: {fname}")
            continue

        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        ret, corners = cv2.findChessboardCorners(gray, checkerboard_size, None)
        if ret:
            objpoints.append(objp)
            corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
            imgpoints.append(corners2)

            image = cv2.drawChessboardCorners(image, checkerboard_size, corners2, ret)
            # plt.figure()
            # plt.imshow(image)
            # plt.title(fname)


    if not objpoints:
        raise ValueError("No checkerboards detected. Check paths or images.")

    ret, K, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
    return ret, K, dist, rvecs, tvecs


def undistort_image(image: np.ndarray, K: np.ndarray, dist: np.ndarray) -> np.ndarray:
    h, w = image.shape[:2]
    new_K, roi = cv2.getOptimalNewCameraMatrix(K, dist, (w, h), 1, (w, h))
    undistorted = cv2.undistort(image, K, dist, None, new_K)
    x, y, w, h = roi
    undistorted = undistorted[y:y + h, x:x + w]
    return undistorted
