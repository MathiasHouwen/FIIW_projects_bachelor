from os.path import abspath, dirname, join
from tensorflow.keras.models import load_model
from training import train_main
from webcam_test import webcam_main


# -------- CONFIG --------
# MODE = 'TRAIN'
MODE = 'PLAY'
IMAGE_SIZE = (224, 224)
DATA_PATH = abspath(join(dirname(__file__), '..', 'Data'))
GRAY = False

if MODE == 'TRAIN':
    model = train_main(IMAGE_SIZE, DATA_PATH, GRAY)
    model.save("trained_model.h5")
    model.save_weights("trained_model_weights.h5")
else:
    model = load_model("trained_model.h5")
    model.load_weights("trained_model_weights.h5")

    webcam_main(model, IMAGE_SIZE, GRAY)  # Uncomment to test
