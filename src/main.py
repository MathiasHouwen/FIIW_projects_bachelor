from os.path import abspath, dirname, join
from tensorflow import config as tf_config
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout, BatchNormalization
from tensorflow.keras.optimizers import Adam
from utils import load_images
from visualisation import plot_history
from webcam_test import webcam


# -------- CONFIG --------
gpus = tf_config.experimental.list_physical_devices('GPU')
print("GPU devices:", gpus)
IMAGE_SIZE = (224, 224)
DATA_PATH = abspath(join(dirname(__file__), '..', 'Data'))

# -------- LOAD DATASET --------
(x_train, y_train), (x_test, y_test) = load_images(DATA_PATH, IMAGE_SIZE)

# -------- CUSTOM CNN --------

def build_custom_model():
    model = Sequential([
        Conv2D(32, (5, 5), activation='relu', input_shape=(224, 224, 3)),
        BatchNormalization(),
        MaxPooling2D(2, 2),

        Conv2D(64, (3, 3), activation='relu'),
        BatchNormalization(),
        MaxPooling2D(2, 2),

        # Conv2D(128, (3, 3), activation='relu'),  # Added 3rd conv layer
        # BatchNormalization(),
        # MaxPooling2D(2, 2),

        Flatten(),
        Dense(128, activation='relu'),
        Dropout(0.4),
        Dense(1, activation='sigmoid')
    ])
    model.compile(optimizer=Adam(), loss='binary_crossentropy', metrics=['accuracy'])
    return model


model = build_custom_model()
history = model.fit(x_train, y_train, epochs=20, validation_data=(x_test, y_test))

plot_history(history)
# webcam(model, IMAGE_SIZE)  # Uncomment to test
