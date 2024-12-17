#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Team names comma separated"
__version__ = "0.1.0"
__license__ = "GPLv3"

import argparse
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_absolute_percentage_error


def loadData(file_path):
    """
    Load data from a CSV file
    """
    try:
        data = pd.read_csv(file_path)
        return data
    except Exception as e:
        print(f"Error loading file {file_path}: {e}")
        return None


def lineaireRegresionModel(X_train, y_train, intercept=False, scaler=False):
    """
    Train a Linear Regression model with optional intercept and scaling
    """
    # Optional scaling
    scaler_obj = None
    if scaler:
        scaler_obj = StandardScaler()
        X_train = scaler_obj.fit_transform(X_train)

    # Train the model
    model = LinearRegression(fit_intercept=intercept)
    model.fit(X_train, y_train)

    return model, scaler_obj


def calculateMAPE(y_true, y_pred):
    """
    Calculate Mean Absolute Percentage Error (MAPE)
    """
    return mean_absolute_percentage_error(y_true, y_pred)


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


def main(args):
    """ Main entry point of the app """
    training_data = loadData(args.training_file)
    testing_data = loadData(args.testing_file)

    if training_data is None or testing_data is None:
        print("Failed to load the data.")
        return

    mape = 0.0

    X_train = training_data[['Open', 'High', 'Low']].values
    y_train = training_data['Last Close'].values
    X_test = testing_data[['Open', 'High', 'Low']].values
    y_test = testing_data['Last Close'].values

    model, scaler_obj = lineaireRegresionModel(X_train, y_train, intercept=True, scaler=True)
    if scaler_obj:
        X_test = scaler_obj.transform(X_test)

    y_pred = model.predict(X_test)
    mape = calculateMAPE(y_test, y_pred)

    print("MAPE: {:.2f}%".format(mape * 100))
    plot_testing_data_with_predictions(X_test, y_test, y_pred)


if __name__ == "__main__":
    """ This is executed when run from the command line """
    parser = argparse.ArgumentParser()

    # Required positional argument
    parser.add_argument("training_file", help="Training data file")
    parser.add_argument("testing_file", help="Testing data file")

    # Specify output of "--version"
    parser.add_argument(
        "--version",
        action="version",
        version="%(prog)s (version {version})".format(version=__version__))

    args = parser.parse_args()
    main(args)
