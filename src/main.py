from typing import Callable, Optional, Any

from matplotlib import pyplot as plt

from src.processing import boxes_with_ssim
from src.utils.images_io import *
from src.utils.preprocesing import fourier_transform, magnitude_transform, gaussian_filter, inverse_fourier_transform, \
    remove_periodische_ruis

BASE_PATH = './../images'
PROCESS_PARAMS = {
    'test_1': {},
    'test_4': {
        '01': {'notch': (540, 140)},
        '05': {'notch': (450, 220)}
    }
}

def handle_test_1(test:MatLike, template:MatLike) -> MatLike:
    return boxes_with_ssim(test, template)

def handle_test_4(test:MatLike, template:MatLike, params:dict) -> MatLike:
    filtered = remove_periodische_ruis(test, params['notch'])
    return boxes_with_ssim(filtered, template)


def do(test_dir_name:str, process:Callable[..., MatLike], gray=False):
    folder = ImageFolder(BASE_PATH, test_dir_name, gray)
    folder.clean_and_make_out_folder()
    for image_pair in folder.images:
        params = PROCESS_PARAMS[test_dir_name].get(image_pair.pcb_id)
        out_img = process(image_pair.test, image_pair.template, params) if params else process(image_pair.test,image_pair.template)
        folder.write_out_image(out_img, image_pair)


def main():
    # removenoise_test_4()

    # do('test_1', handle_test_1, True)
    do('test_4', handle_test_4, True)

if __name__ == '__main__':
    main()