import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from matplotlib.axes import Axes
from matplotlib.figure import Figure


def linear_function(x, intercept, slope):
    return intercept + slope * x

def plot_data_with_regression_line(x_features: pd.DataFrame, regression_weights: list[float], regression_intercept: float):
    fig:Figure
    axes:Axes
    fig, axes = plt.subplots(1, 3, figsize=(15, 6), sharey=True)
    for i, featureName in enumerate(x_features.columns):
        # data
        y_points_data = x_features[featureName].values
        x_points_data = range(len(y_points_data))
        axes[i].scatter(x_points_data ,y_points_data, color='green', label=f"Test data: {featureName}", alpha=0.6)

        # regression line
        slope = regression_weights[i]
        intercept = regression_intercept
        x_points_regr = x_points_data
        y_points_regr = [linear_function(x, intercept, slope) for x in x_points_data]
        axes[i].plot(x_points_regr, y_points_regr, color='orange', label='Linear Regression', linewidth=2)

        axes[i].set_ylabel('price', fontsize=12)
        axes[i].grid(True)
        axes[i].legend()

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