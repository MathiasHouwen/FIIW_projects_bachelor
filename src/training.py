import numpy as np
from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
from tensorflow import config as tf_config
from tensorflow.keras.models import Sequential, Model, load_model
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout, BatchNormalization, GlobalAveragePooling2D, Input
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from utils import load_images
from visualisation import plot_history, show_augmentations

# -------- LOAD DATASET --------



# -------- CUSTOM CNN --------

def build_custom_model(gray):
    base_model = MobileNetV2(include_top=False, weights='imagenet', input_shape=(224, 224, 1 if gray else 3))
    base_model.trainable = True
    for layer in base_model.layers[:-20]:  # Freeze all but last 20 layers
        layer.trainable = False

    inputs = Input(shape=(224, 224, 3))
    x = base_model(inputs, training=False)
    x = GlobalAveragePooling2D()(x)
    x = Dropout(0.3)(x)
    outputs = Dense(1, activation='sigmoid')(x)

    model = Model(inputs, outputs)
    model.compile(optimizer=Adam(learning_rate=1e-5), loss='binary_crossentropy', metrics=['accuracy'])
    return model


def train_datagen():
    return ImageDataGenerator(
    preprocessing_function=preprocess_input,
    horizontal_flip=True
    
    # rescale=1./255,
    # rotation_range=3,
    # zoom_range=0.4,
    # shear_range=1,
    # width_shift_range=0.05,
    # height_shift_range=0.05,
    # brightness_range=[0.9, 1.1],
    # horizontal_flip=True,
    # fill_mode='nearest'
)
def test_datagen():
    return ImageDataGenerator(
    preprocessing_function=preprocess_input,
    # rescale=1./255
)

def train_main(imsize, datapath, gray):
    gpus = tf_config.experimental.list_physical_devices('GPU')
    print("GPU devices:", gpus)
    
    
    (x_train, y_train), (x_test, y_test) = load_images(datapath, imsize, gray)
    if gray:
        x_train = np.expand_dims(x_train, axis=-1) # add one channel dimension cuz gray removes all RGB channels
        x_test = np.expand_dims(x_test, axis=-1)
        
    show_augmentations(train_datagen(), x_train[0])    

    model = build_custom_model(gray)
    train_generator = train_datagen().flow(x_train, y_train, batch_size=16)
    val_generator = test_datagen().flow(x_test, y_test)
    history = model.fit(train_generator, epochs=20, validation_data=val_generator)
    
    plot_history(history)
    return model

