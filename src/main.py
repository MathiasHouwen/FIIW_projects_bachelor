from typing import Callable

from src.processing import *
from src.utils.images_io import *
from src.utils.preprocesing import *
from config import BASE_PATH, PROCESS_PARAMS

PLOT_SSIM = True


def handle_raw(test:MatLike, template:MatLike, test_raw:MatLike) -> tuple[MatLike, MatLike]:
    return boxes_with_ssim(test, template, test_raw, plot=PLOT_SSIM), test

def handle_periodic_noise(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> tuple[MatLike, MatLike]:
    filtered = remove_periodische_ruis(test, params['notch'])
    return boxes_with_ssim(filtered, template, test_raw, plot=PLOT_SSIM), filtered

def handle_median_filter(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> tuple[MatLike, MatLike]:
    filtered_test = median(test)
    filtered_template = median(template)
    min_defect, thresh = params['min_defect_area'], params['thresh']
    return boxes_with_ssim(filtered_test, filtered_template, test_raw, min_defect_area=min_defect, thresh=thresh, plot=PLOT_SSIM), filtered_test

def handle_gaussian_filter(test:MatLike, template:MatLike, test_raw:MatLike, params:dict) -> tuple[MatLike, MatLike]:
    filtered_test = gaussian(test)
    filtered_template = gaussian(template)
    min_defect, thresh = params['min_defect_area'], params['thresh']
    return boxes_with_ssim(filtered_test, filtered_template, test_raw, min_defect_area=min_defect, thresh=thresh, plot=PLOT_SSIM), filtered_test

def handle_feature_matching(test:MatLike, template:MatLike, test_raw:MatLike):
    corrected_test, inv_corrected_templ = feature_matching_undo_transform(test, template)
    # corrected test doet een 'undo' op de transfrom van de test, bewijst dat de feature matching + homography werkt
    # inv_corrected_templ gaat de inverse 'correctie' op de template doen. Dan kan SSIM daarop en blijft de output in perspectief van de test img
    return boxes_with_ssim(test, inv_corrected_templ, test_raw, plot=PLOT_SSIM), corrected_test


def main():
    # do('test_1', handle_raw, True)
    # do('test_2', handle_gaussian_filter, True)
    # do('test_3', handle_median_filter, True)
    # do('test_4', handle_periodic_noise, True)
    do('test_5', handle_feature_matching, True)

    plt.show()

def do(test_dir_name:str, process:Callable[..., MatLike], gray=False):
    print(f"handling test_dir: {test_dir_name}")
    folder = ImageFolder(BASE_PATH, test_dir_name, gray)
    folder.clean_and_make_out_and_processed_folder()
    num_of_images = len(folder.images)
    for i, image_pair in enumerate(folder.images):
        params = PROCESS_PARAMS[test_dir_name].get(image_pair.pcb_id)
        out_img, proc_img = process(image_pair.test, image_pair.template, image_pair.test_raw, params) if params else process(image_pair.test,image_pair.template, image_pair.test_raw)
        folder.write_out_image(out_img, image_pair)
        folder.write_processed_image(proc_img, image_pair)
        print(f"  -> processed {i+1}/{num_of_images} images")

if __name__ == '__main__':
    main()