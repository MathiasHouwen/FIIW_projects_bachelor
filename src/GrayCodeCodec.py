import math
from dataclasses import dataclass

import cv2
import numpy as np
from typing import Callable

from matplotlib import pyplot as plt

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

    def apply_to_all(self, func: Callable[[np.ndarray], np.ndarray]):
        return FramesGroup(
            h=func(self.h),
            h_inv=func(self.h_inv),
            v=func(self.v),
            v_inv=func(self.v_inv),
        )

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

    def decode_frames(self, threshold:int = 100) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
        horizontal_codes = np.zeros((self.rows, self.cols), dtype=np.int16)
        vertical_codes = np.zeros((self.rows, self.cols), dtype=np.int16)
        # mask is voor onzeker pixels.
        #  - onzeker pixel: het 'dark' / 'light' result is dezelfde waarde voor de normal en inverted image
        mask = np.zeros((self.rows, self.cols), dtype=np.uint8)

        for frame_group, bit_index in self._frames_grouped_iterator():
            gray_group = frame_group.apply_to_all(lambda img: cv2.cvtColor(img, cv2.COLOR_BGR2GRAY))
            gray_group_int = gray_group.apply_to_all(lambda img: img.astype(np.int16)) # -255 tot 255

            h_delta = gray_group_int.h - gray_group_int.h_inv # -255 tot 255
            v_delta = gray_group_int.v - gray_group_int.v_inv

            # als normal 'veel'(threshold) hoger is dan inv, dan is die lit
            # lit = 255, dark = -255, unsure = 0
            h_lit, h_unsure  = h_delta >= threshold, abs(h_delta) < threshold
            v_lit, v_unsure = v_delta >= threshold, abs(v_delta) < threshold

            horizontal_codes[h_lit] |= (1 << bit_index)
            vertical_codes[v_lit] |= (1 << bit_index)

            mask |= h_unsure | v_unsure

        return self._graycode_to_binary(horizontal_codes), self._graycode_to_binary(vertical_codes), mask

    def set_frame(self, depth: int, frame: np.ndarray):
        self.frames[depth] = frame

    def _frames_grouped_iterator(self):
        for n in range(0, self.n//2, 2):
            group = FramesGroup(h=self.frames[n],
                                h_inv=self.frames[n+1],
                                v=self.frames[self.n//2 + n],
                                v_inv=self.frames[self.n//2 + n+1],)
            group.validate_not_none()
            num_of_bits = self.n//4
            yield group, num_of_bits - n // 2 - 1 # omdat het de MSB eerst is en niet LSB

    @staticmethod
    def _graycode_to_binary(gray: np.ndarray) -> np.ndarray:
        binary = gray.copy()
        shift = 1
        while (gray >> shift).any():
            binary ^= (gray >> shift)
            shift += 1
        return binary
