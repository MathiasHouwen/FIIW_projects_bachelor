from os.path import abspath, dirname, join
import numpy as np
import cv2
import matplotlib.pyplot as plt

from tensorflow import config as tf_config
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from tensorflow.keras.optimizers import Adam

from utils import load_images

print("TensorFlow GPU devices:", tf_config.list_physical_devices('GPU'))

# -------- CONFIG --------
IMAGE_SIZE = (224, 224)
DATA_PATH = abspath(join(dirname(__file__), '..', 'Data'))

# -------- LOAD DATASET --------
(x_train, y_train), (x_test, y_test) = load_images(DATA_PATH, IMAGE_SIZE)

# -------- CUSTOM CNN --------
def build_custom_model():
    model = Sequential([
        Conv2D(32, (3, 3), activation='relu', input_shape=(IMAGE_SIZE[0], IMAGE_SIZE[1], 3)),
        MaxPooling2D(2, 2),
        Conv2D(64, (3, 3), activation='relu'),
        MaxPooling2D(2, 2),
        Flatten(),
        Dense(64, activation='relu'),
        Dense(1, activation='sigmoid')
    ])
    model.compile(optimizer=Adam(), loss='binary_crossentropy', metrics=['accuracy'])
    return model

model = build_custom_model()
history = model.fit(x_train, y_train, epochs=10, validation_data=(x_test, y_test))

# -------- PLOT TRAINING --------
def plot_history(history, title="Model Accuracy"):
    plt.plot(history.history['accuracy'], label='Train Acc')
    plt.plot(history.history['val_accuracy'], label='Val Acc')
    plt.title(title)
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()

plot_history(history)

# -------- WEBCAM TESTING --------
def webcam(model, preprocess=None):
    cap = cv2.VideoCapture(0)
    print("Press 'q' to quit.")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        input_img = cv2.resize(frame, IMAGE_SIZE)
        input_img = np.expand_dims(input_img, axis=0).astype('float32')

        input_img = preprocess(input_img) if preprocess else input_img / 255.0
        pred = model.predict(input_img)[0][0]
        label = "Gesture" if pred > 0.5 else "No Gesture"

        cv2.putText(frame, f"{label} ({pred:.2f})", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0) if pred > 0.5 else (0, 0, 255), 2)

        cv2.imshow('Gesture Prediction', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

# webcam(model)  # Uncomment to test
