from os.path import abspath, dirname, join
from tensorflow import config as tf_config
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout, BatchNormalization
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from utils import load_images
from visualisation import plot_history, show_augmentations
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
        Conv2D(32, (5, 5), activation='relu', input_shape=(IMAGE_SIZE[0], IMAGE_SIZE[1], 3)),
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


train_datagen = ImageDataGenerator(
    rescale=1./255,
    rotation_range=5,
    width_shift_range=0.1,
    height_shift_range=0.05,
    zoom_range=0.4,
    brightness_range=[0.5, 1.5],
    shear_range=2,
    fill_mode='nearest',
    horizontal_flip=True
)
test_datagen = ImageDataGenerator(rescale=1./255)

show_augmentations(train_datagen, x_train[0])


model = build_custom_model()
train_generator = train_datagen.flow(x_train, y_train, batch_size=16)
val_generator = test_datagen.flow(x_test, y_test)
history = model.fit(train_generator, epochs=20, validation_data=val_generator)



plot_history(history)
# webcam(model, IMAGE_SIZE)  # Uncomment to test
