import cv2
import numpy as np
import pyautogui
import time
from keras import *
from keras.src.saving import load_model


class GestureGameController:
    def __init__(self, model_path, image_size=(224, 224), threshold=0.5, cooldown=1.0):
        self.model = load_model(model_path)
        self.image_size = image_size
        self.threshold = threshold
        self.cooldown = cooldown
        self.last_action_time = 0
        self.cap = cv2.VideoCapture(0)

    def preprocess(self, frame):
        img = cv2.resize(frame, self.image_size)
        img = img.astype("float32") / 255.0
        return np.expand_dims(img, axis=0)

    def detect_and_act(self):
        print("Gesture control started. Press 'q' to quit.")
        while True:
            ret, frame = self.cap.read()
            if not ret:
                break

            img = self.preprocess(frame)
            pred = self.model.predict(img)[0][0]

            if pred > self.threshold and time.time() - self.last_action_time > self.cooldown:
                self.perform_action()
                self.last_action_time = time.time()
                label = "Gesture Detected"
            else:
                label = "No Gesture"

            self.display_frame(frame, label, pred)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        self.cleanup()

    def perform_action(self):
        print("Performing action: SPACE")
        pyautogui.keyDown('space')
        time.sleep(0.1)
        pyautogui.keyUp('space')

    def display_frame(self, frame, label, pred):
        cv2.putText(frame, f"{label} ({pred:.2f})", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1,
                    (0, 255, 0) if pred > self.threshold else (0, 0, 255), 2)
        cv2.imshow('Gesture Game Control', frame)

    def cleanup(self):
        self.cap.release()
        cv2.destroyAllWindows()
        print("Gesture control stopped.")