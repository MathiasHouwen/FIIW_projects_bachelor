import tensorflow as tf
import keras
from keras import layers
import matplotlib.pyplot as plt

from utils import load_images

path = ""
image_size = 0

# Load dataset
(x_train, y_train), (x_test, y_test) = load_images("./Data", image_size)

# Create CNN
num_classes = 2

model = keras.Sequential([
    keras.Input(shape=(image_size, image_size, 1)),  # Or 3 if RGB images
    layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),
    layers.MaxPooling2D(pool_size=(2, 2)),
    layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
    layers.MaxPooling2D(pool_size=(2, 2)),
    layers.Flatten(),
    layers.Dropout(0.5),
    layers.Dense(num_classes, activation="softmax"),
])

model.compile(loss="sparse_categorical_crossentropy", optimizer="adam", metrics=["accuracy"])

# Train data
history = model.fit(
    x_train, y_train,
    batch_size=32,
    epochs=15,
    validation_split=0.1  # 10% of training data for validation
)

plt.figure(figsize=(12, 4))

plt.subplot(1, 2, 1)
plt.plot(history.history['accuracy'], label='train acc')
plt.plot(history.history['val_accuracy'], label='val acc')
plt.title('Accuracy')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(history.history['loss'], label='train loss')
plt.plot(history.history['val_loss'], label='val loss')
plt.title('Loss')
plt.legend()

plt.show()

# Evaluation
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=2)
print(f"Test accuracy: {test_acc:.2f}")