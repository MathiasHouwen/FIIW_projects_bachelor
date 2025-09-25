from os.path import abspath, dirname, join
from tensorflow.keras.models import load_model
from training import train_main
from webcam_test import webcam_main
from game_controller import GestureGameController


# -------- CONFIG --------
MODE = 'TRAIN'
# MODE = 'PLAY'
# MODE = 'TEST'
IMAGE_SIZE = (224, 224)
DATA_PATH = abspath(join(dirname(__file__), '..', 'Data'))
GRAY = True

if MODE == 'TRAIN':
    model = train_main(IMAGE_SIZE, DATA_PATH, GRAY)
    model.save("trained_model.h5")
    model.save_weights("trained_model_weights.h5")
elif MODE == 'TEST':
    model = load_model("trained_model.h5")
    model.load_weights("trained_model_weights.h5")

    webcam_main(model, IMAGE_SIZE, GRAY, threshold=75)  # Uncomment to test
else:
    model = load_model("trained_model.h5")
    model.load_weights("trained_model_weights.h5")
    controller = GestureGameController(
        model=model,
        image_size=IMAGE_SIZE,
        threshold=75
    )

    controller.detect_and_act()
