import matplotlib.pyplot as plt

def plot_testing_data_with_predictions(X_test, y_test, y_pred_test):
    # Ensure X_test has 3 columns
    if X_test.shape[1] != 3:
        raise ValueError("X_test should have exactly 3 columns.")

    # Create a figure with 3 subplots
    fig, axes = plt.subplots(1, 3, figsize=(15, 6), sharey=True)

    # Loop over the 3 columns of X_test
    for i in range(3):
        axes[i].scatter(X_test[:, i], y_test, color='green', label='Actual Testing Data', alpha=0.6)
        axes[i].plot(X_test[:, i], y_pred_test, color='orange', label='Predicted Regression Line', linewidth=2)
        axes[i].set_title(f"Feature {i + 1}: Testing Data vs. Predictions", fontsize=14)
        axes[i].set_xlabel(f'Feature {i + 1}', fontsize=12)
        axes[i].set_ylabel('Last Close', fontsize=12)
        axes[i].grid(True)
        axes[i].legend()

    # Adjust layout and show plot
    plt.tight_layout()
    plt.show()