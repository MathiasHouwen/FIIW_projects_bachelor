import math
from dataclasses import dataclass

import cv2
import numpy as np
from typing import Tuple

from codec import Encoder, Decoder


def binary_to_gray(num: int) -> int:
    """
    The purpose of this function is to convert an unsigned
    binary number to reflected binary Gray code.

    The operator >> is shift right. The operator ^ is exclusive or.
    Source: http://en.wikipedia.org/wiki/Gray_code
    """
    return (num >> 1) ^ num


def get_bit(decimal: int, n: int) -> int:
    """
    Function takes the decimal number
    Function takes the Nth bit (1 to 31)
    Return the value of Nth bit from decimal
    Source: http://icfun.blogspot.com/2009/04/get-n-th-bit-value-of-any-integer.html
    """
    constant = 1 << (n - 1)
    return 1 if decimal & constant else 0


class GrayCodeEncoder(Encoder):
    def __init__(self, rows: int, cols: int, depth: int):
        super().__init__(cols, rows)
        self.n = depth * 4  # number of frames to be computed
        self.patterns = []

        n_horiz_bits = math.ceil(math.log2(float(self.cols)))
        n_vert_bits = math.ceil(math.log2(float(self.rows)))

        # compute horizontal encoding patterns
        for i in range(depth):
            pattern = np.zeros((1, cols, 3), np.uint8)
            # loop through columns in first row
            for j in range(cols):
                gray = binary_to_gray(j)
                # amplitude of channels
                amp = get_bit(gray, n_horiz_bits - i)
                pattern[0, j] = [255.0 * amp, 255.0 * amp, 255.0 * amp]
            self.patterns.append(pattern)
            self.patterns.append(cv2.bitwise_not(pattern))

        # compute vertical encoding patterns
        for i in range(depth):
            pattern = np.zeros((rows, 1, 3), np.uint8)
            # Loop through rows in first column
            for j in range(rows):
                gray = binary_to_gray(j)
                # Amplitude of channels
                amp = get_bit(gray, n_vert_bits - i)
                pattern[j, 0] = [255.0 * amp, 255.0 * amp, 255.0 * amp]
            self.patterns.append(pattern)
            self.patterns.append(cv2.bitwise_not(pattern))

    def get_encoding_pattern(self, depth) -> np.array:
        return self.patterns[depth]

@dataclass
class FramesGroup:
    h:np.ndarray|None
    v:np.ndarray|None
    h_inv:np.ndarray|None
    v_inv:np.ndarray|None

    def validate_not_none(self):
        if any(x is None for x in [self.h, self.v, self.h_inv, self.v_inv]):
            raise ValueError("Ik heb toch niks aan lege frames")

class GrayCodeDecoder(Decoder):
    def __init__(self, cols: int, rows: int, depth: int):
        super().__init__(cols, rows)
        self.n = depth * 4
        # volgorde:
        # - eerst depth*2 x horizontal images
        # - dan depth*2 x vertical images
        #   - elke groep van depth*2 images =
        #     - normal frame 0
        #     - inverted frame 0
        #     - normal frame 1
        #     - inverted frame 1
        #     ...
        #     - normal frame depth-1
        #     - inverted frame depth-1
        self.frames = self.n * [None]

    def decode_frames(self) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
        horizontal_codes = np.zeros((self.cols, self.rows))
        vertical_codes = np.zeros((self.cols, self.rows))
        # mask is voor onzeker pixels.
        #  - onzeker pixel: het 'dark' / 'light' result is dezelfde waarde voor de normal en inverted image
        mask = np.zeros((self.cols, self.rows))

        for frame_group in self._frames_grouped_iterator():
            horizontal = frame_group.h
            vertical = frame_group.v
            horizontal_inverted = frame_group.h_inv
            vertical_inverted = frame_group.v_inv



        return horizontal_codes, vertical_codes, mask

    def set_frame(self, depth: int, frame: np.ndarray):
        self.frames[depth] = frame

    def _frames_grouped_iterator(self):
        for n in range(0, self.n//2, 2):
            group = FramesGroup(h=self.frames[n],
                                v=self.frames[n+1],
                                h_inv=self.frames[self.n//2 + n],
                                v_inv=self.frames[self.n//2 + n+1])
            group.validate_not_none()
            yield group
