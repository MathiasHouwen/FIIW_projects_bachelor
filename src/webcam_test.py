import numpy as np
import cv2
def webcam(model, imsize, preprocess=None):
    cap = cv2.VideoCapture(0)
    print("Press 'q' to quit.")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        input_img = cv2.resize(frame, imsize)
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