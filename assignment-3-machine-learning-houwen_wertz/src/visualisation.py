import matplotlib.pyplot as plt
import numpy as np


import matplotlib.pyplot as plt

def plot_history(history, title="Model Performance"):
    fig, axs = plt.subplots(1, 2, figsize=(12, 5))

    # Accuracy plot
    axs[0].plot(history.history['accuracy'], label='Train Acc')
    axs[0].plot(history.history['val_accuracy'], label='Val Acc')
    axs[0].set_title(f"{title} - Accuracy")
    axs[0].set_xlabel('Epoch')
    axs[0].set_ylabel('Accuracy')
    axs[0].legend()

    # Loss plot
    axs[1].plot(history.history['loss'], label='Train Loss')
    axs[1].plot(history.history['val_loss'], label='Val Loss')
    axs[1].set_title(f"{title} - Loss")
    axs[1].set_xlabel('Epoch')
    axs[1].set_ylabel('Loss')
    axs[1].legend()

    plt.tight_layout()
    plt.show()



def show_augmentations(datagen, sample_img):
    sample_img = np.expand_dims(sample_img, axis=0)

    aug_iter = datagen.flow(sample_img, batch_size=1)
    plt.figure(figsize=(12, 6))
    for i in range(10):
        augmented_img = next(aug_iter)[0]  # Get the image
        plt.subplot(2, 5, i + 1)
        plt.imshow(augmented_img)
        plt.axis('off')
        plt.title(f'Aug {i+1}')
    plt.tight_layout()
    plt.show()