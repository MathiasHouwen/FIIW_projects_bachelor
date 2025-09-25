from dataclasses import dataclass

import numpy as np

@dataclass(frozen=True)
class Code:
    h: int
    v: int

@dataclass
class Coord: # does not need to be hashed, so not frozen=true
    y: int
    x: int

def get_coordinates(dec_h, dec_v, mask) -> tuple[list[Coord], list[Code]]:
    valid_mask = mask == 0  # 0 means valid
    ys, xs = np.nonzero(valid_mask)
    coords = [Coord(y, x) for y, x in zip(ys, xs)]
    codes = [Code(int(h), int(v)) for h, v in zip(dec_h[valid_mask], dec_v[valid_mask])]
    return coords, codes

def build_dict(coords: list[Coord], codes: list[Code]) -> dict[Code, Coord]:
    code_dict = {}
    # duplicates_count = 0
    for coord, code in zip(coords, codes):
        code_dict[code] = coord
    #     if code in code_dict:
    #         duplicates_count += 1
    #         code_dict[code] = None # als er 2 duplicate graycodes zijn kunnen we die niet vertrouwen want je weet later niet welke van de 2 bij welke match hoort
    #     else:
    #         code_dict[code] = coord
    # code_dict = {k: v for k, v in code_dict.items() if v is not None}
    # print(f"removed {duplicates_count} duplicate graycodes. Good matches: {len(code_dict)}")
    return code_dict

def match_coordinates(dict1: dict[Code, Coord], dict2: dict[Code, Coord]) -> tuple[np.ndarray, np.ndarray]:
    shared_codes = set(dict1.keys()) & set(dict2.keys())
    pts1 = np.array([[dict1[code].x, dict1[code].y] for code in shared_codes], dtype=np.float32)
    pts2 = np.array([[dict2[code].x, dict2[code].y] for code in shared_codes], dtype=np.float32)
    return pts1, pts2

def get_matches_for_essentialMat(gray_h_l, gray_v_l, mask_l,
                                 gray_h_r, gray_v_r, mask_r):
    coords_l, codes_l = get_coordinates(gray_h_l, gray_v_l, mask_l)
    coords_r, codes_r = get_coordinates(gray_h_r, gray_v_r, mask_r)

    dict_l = build_dict(coords_l, codes_l)
    dict_r = build_dict(coords_r, codes_r)

    pts_l, pts_r = match_coordinates(dict_l, dict_r)
    return pts_l, pts_r


