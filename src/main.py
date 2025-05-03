import tensorflow as tf
import keras
import cv2
import os
import numpy as np
from keras import layers
import matplotlib.pyplot as plt

from utils import load_images

# -------- CONFIG --------
IMAGE_SIZE = (224, 224)
DATA_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'Data'))

# -------- LOAD DATASET --------
(x_train, y_train), (x_test, y_test) = load_images(DATA_PATH, IMAGE_SIZE)

# -------- CUSTOM CNN --------
def build_custom_model():
    model = keras.Sequential([
        layers.Conv2D(32, (3, 3), activation='relu', input_shape=(IMAGE_SIZE[0], IMAGE_SIZE[1], 3)),
        layers.MaxPooling2D(2, 2),
        layers.Conv2D(64, (3, 3), activation='relu'),
        layers.MaxPooling2D(2, 2),
        layers.Flatten(),
        layers.Dense(64, activation='relu'),
        layers.Dense(1, activation='sigmoid')  # Binary classification
    ])
    model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    return model

model_custom = build_custom_model()
history_custom = model_custom.fit(x_train, y_train, epochs=10, validation_data=(x_test, y_test))

# -------- EVALUATE & PLOT --------
def plot_history(history, title="Model Accuracy"):
    plt.plot(history.history['accuracy'], label='Train Acc')
    plt.plot(history.history['val_accuracy'], label='Val Acc')
    plt.title(title)
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()

plot_history(history_custom, "Custom CNN Accuracy")

# -------- TESTING CUSTOM MODEL --------
def test_webcam(model, preprocess=None):
    cap = cv2.VideoCapture(0)
    print("Press 'q' to quit.")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        input_img = cv2.resize(frame, (IMAGE_SIZE, IMAGE_SIZE))
        input_img = np.expand_dims(input_img, axis=0).astype('float32')

        if preprocess:
            input_img = preprocess(input_img)
        else:
            input_img /= 255.0

        pred = model.predict(input_img)[0][0]
        label = "Gesture" if pred > 0.5 else "No Gesture"

        cv2.putText(frame, f"{label} ({pred:.2f})", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0) if pred > 0.5 else (0, 0, 255), 2)

        cv2.imshow('Gesture Prediction', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

test_webcam(model_custom)  # Uncomment to test