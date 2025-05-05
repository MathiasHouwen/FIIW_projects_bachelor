import matplotlib.pyplot as plt
import numpy as np

def plot_history(history, title="Model Accuracy"):
    plt.plot(history.history['accuracy'], label='Train Acc')
    plt.plot(history.history['val_accuracy'], label='Val Acc')
    plt.title(title)
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
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