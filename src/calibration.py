import cv2
import numpy as np
import glob


def calibrate_camera_from_checkerboard(images_path_pattern: str, checkerboard_size = (9, 7), square_size=1.0):
    """
    Calibrate camera from checkerboard images.

    Args:
        images_path_pattern: Path pattern to find checkerboard images (e.g., 'calib/*.png').
        checkerboard_size: (rows, cols) of inner corners on checkerboard.
        square_size: Size of one square on the checkerboard, in your preferred unit (e.g., cm).

    Returns:
        ret: Reprojection error
        K: Camera matrix
        dist: Distortion coefficients
        rvecs: Rotation vectors
        tvecs: Translation vectors
    """
    # Criteria for cornerSubPix
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    objp = np.zeros((checkerboard_size[0] * checkerboard_size[1], 3), np.float32)
    objp[:, :2] = np.mgrid[0:checkerboard_size[1], 0:checkerboard_size[0]].T.reshape(-1, 2)
    objp *= square_size

    objpoints = []  # 3D points in real world
    imgpoints = []  # 2D points in image

    image_files = glob.glob(images_path_pattern)
    print(f"Found {len(image_files)} images: {image_files}")
    for fname in image_files:
        image = cv2.imread(fname)
        if image is None:
            print(f"Failed to load: {fname}")
            continue

        img = cv2.imread(fname)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        ret, corners = cv2.findChessboardCorners(gray, checkerboard_size, None)
        if ret:
            objpoints.append(objp)
            corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
            imgpoints.append(corners2)

            img = cv2.drawChessboardCorners(img, checkerboard_size, corners2, ret)
            cv2.imshow('Corners', img)
            cv2.waitKey(100)

    if not objpoints:
        raise ValueError("No checkerboards detected. Check paths or images.")

    ret, K, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
    return ret, K, dist, rvecs, tvecs


def undistort_image(image: np.ndarray, K: np.ndarray, dist: np.ndarray) -> np.ndarray:
    """
    Undistort an image using the camera matrix and distortion coefficients.
    """
    h, w = image.shape[:2]
    new_K, roi = cv2.getOptimalNewCameraMatrix(K, dist, (w, h), 1, (w, h))
    undistorted = cv2.undistort(image, K, dist, None, new_K)
    return undistorted
