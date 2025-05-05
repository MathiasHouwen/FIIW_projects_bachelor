import cv2
import numpy as np
import pyautogui
import time


class GestureGameController:
    def __init__(self, model, image_size=(224, 224), threshold=75, cooldown_seconds=0.5):
        self.model = model
        self.image_size = image_size
        self.threshold = threshold
        self.cooldown_seconds = cooldown_seconds
        self.last_action_time = 0
        self.gesture_active = False
        self.cap = cv2.VideoCapture(0)

    def preprocess(self, frame):
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        img = cv2.resize(frame, self.image_size)
        img = np.expand_dims(img, axis=0).astype('float32')
        return img / 255.0

    def detect_and_act(self):
        print("Gesture control started. Press 'q' to quit.")
        while True:
            ret, frame = self.cap.read()
            if not ret:
                break

            img = self.preprocess(frame)
            pred = (1 - self.model.predict(img, verbose=0)[0][0]) * 100
            gesture_detected = pred > self.threshold
            current_time = time.time()

            if gesture_detected:
                if not self.gesture_active and (current_time - self.last_action_time) > self.cooldown_seconds:
                    self.perform_action()
                    self.last_action_time = current_time
                    self.gesture_active = True
                label = "Mondje open"
            else:
                self.gesture_active = False
                label = "Mondje dicht"

            self.display_frame(frame, label, pred)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        self.cleanup()

    def perform_action(self):
        print("Performing action: SPACE")
        pyautogui.press('space')

    def display_frame(self, frame, label, pred):
        cv2.putText(frame, f"{label} ({pred:.2f})", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1,
                    (0, 255, 0) if pred > self.threshold else (0, 0, 255), 2)
        cv2.imshow('Gesture Game Control', frame)

    def cleanup(self):
        self.cap.release()
        cv2.destroyAllWindows()
        print("Gesture control stopped.")
