import os
import shutil

import cv2
from cv2.typing import MatLike


class ImagePair:
    def __init__(self, template_path:str, test_path:str, gray:bool = False):
        self.test_name = os.path.basename(test_path).removesuffix(".jpg")
        self.pcb_id, self.fault_type, self.fault_number = self.test_name[:2], self.test_name[3:-3], self.test_name[-2:]

        full_template_path = f"{template_path}/{self.pcb_id}.JPG"

        print(f"loading {self.test_name} [pcb:{self.pcb_id}, fault:{self.fault_type}, fault_num:{self.fault_number}]")
        print(f"paths: [test={test_path}, template={full_template_path}]")

        self.template = cv2.imread(full_template_path)
        self.test = cv2.imread(test_path)
        self.test_raw = self.test # Test RAW = direct input, test kan grayscale zijn
        if gray:
            self.template = cv2.cvtColor(self.template, cv2.COLOR_BGR2GRAY)
            self.test = cv2.cvtColor(self.test, cv2.COLOR_BGR2GRAY)

class ImageFolder:
    def __init__(self, base_path:str, test_dir_name:str, gray:bool = False):
        self.input_folder = f"{base_path}/{test_dir_name}/input"
        self.output_folder = f"{base_path}/{test_dir_name}/output"
        self.processed_folder = f"{base_path}/{test_dir_name}/processed"

        template_base = f"{base_path}/template_images"
        self.images = [ImagePair(template_base, f"{self.input_folder}/{test_path}", gray) for test_path in os.listdir(self.input_folder)]

    def clean_and_make_out_and_processed_folder(self):
        if os.path.exists(self.output_folder):
            shutil.rmtree(self.output_folder)
        if os.path.exists(self.processed_folder):
            shutil.rmtree(self.processed_folder)
        os.makedirs(self.output_folder)
        os.makedirs(self.processed_folder)


    def write_out_image(self, img:MatLike, input_pair:ImagePair):
        cv2.imwrite(f"{self.output_folder}/{input_pair.test_name}.jpg", img)

    def write_processed_image(self, img:MatLike, input_pair:ImagePair):
        cv2.imwrite(f"{self.processed_folder}/{input_pair.test_name}.jpg", img)