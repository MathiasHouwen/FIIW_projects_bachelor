import numpy as np
import cv2
import numpy as np
import cv2

def webcam_main(model, imsize, gray, preprocess=None):
    cap = cv2.VideoCapture(0)
    print("Press 'q' to quit.")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Convert to grayscale if requested
        if gray:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            input_img = cv2.resize(frame, imsize)
            input_img = np.expand_dims(input_img, axis=-1)  # shape: (H, W, 1)
        else:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)  # convert for consistency with MobileNetV2
            input_img = cv2.resize(frame, imsize)

        # Expand dims to (1, H, W, C) and normalize
        input_img = np.expand_dims(input_img, axis=0).astype('float32')

        if preprocess:
            input_img = preprocess(input_img)
        else:
            input_img = input_img / 255.0  # normalize if no preprocessing function

        # Predict
        pred = model.predict(input_img, verbose=0)[0][0]
        label = "Gesture" if pred > 0.5 else "No Gesture"

        # Display label
        display_frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR) if not gray else cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)
        cv2.putText(display_frame, f"{label} ({pred:.2f})", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0) if pred > 0.5 else (0, 0, 255), 2)

        cv2.imshow('Gesture Prediction', display_frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
