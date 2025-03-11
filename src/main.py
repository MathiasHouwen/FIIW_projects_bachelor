from typing import Callable

from src.processing import boxes_with_ssim
from src.utils.images_io import *
from src.utils.preprocesing import *
from config import BASE_PATH, PROCESS_PARAMS


def handle_raw(test:MatLike, template:MatLike, test_raw:MatLike) -> MatLike:
    return boxes_with_ssim(test, template, test_raw)

def handle_periodic_noise(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> MatLike:
    filtered = remove_periodische_ruis(test, params['notch'])
    return boxes_with_ssim(filtered, template, test_raw)

def handle_median_filter(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> MatLike:
    filtered_test = remove_pepper_and_salt(test)
    filtered_template = remove_pepper_and_salt(template)
    return boxes_with_ssim(filtered_test, filtered_template, test_raw, min_defect_area=params['min_defect_area'], thresh=params['thresh'])


def main():
    # do('test_1', handle_raw, True)
    # do('test_2', handle_median_filter, True)
    do('test_3', handle_median_filter, True)
    do('test_4', handle_periodic_noise, True)

def do(test_dir_name:str, process:Callable[..., MatLike], gray=False):
    folder = ImageFolder(BASE_PATH, test_dir_name, gray)
    folder.clean_and_make_out_folder()
    for image_pair in folder.images:
        params = PROCESS_PARAMS[test_dir_name].get(image_pair.pcb_id)
        out_img = process(image_pair.test, image_pair.template, image_pair.test_raw, params) if params else process(image_pair.test,image_pair.template, image_pair.test_raw)
        folder.write_out_image(out_img, image_pair)

if __name__ == '__main__':
    main()