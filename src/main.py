#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Team names comma separated"
__version__ = "0.1.0"
__license__ = "GPLv3"

import matplotlib.pyplot as plt
import pandas as pd
import argparse

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

from src.models import train
from src.pre_massaging import pre_massage
from src.utils import split_features
from src.visualisation import plot_data_with_regression_line


def calculateMAPE(y_true, y_pred):
    """
    Calculate Mean Absolute Percentage Error (MAPE)
    """
    #return mean_absolute_percentage_error(y_true, y_pred)





def main(args):
    """ Main entry point of the app """
    training_data = pd.read_csv(args.training_file)
    testing_data = pd.read_csv(args.testing_file)

    training_data = pre_massage(training_data)
    testing_data = pre_massage(testing_data)

    x_features_train, y_feature_train = split_features(training_data, 'Last Close')
    x_features_test, y_feature_test = split_features(testing_data, 'Last Close')


    ###
    ### ChatGPT deel
    ### ========================================================================================
    ### ========================================================================================
    ###


    model = LinearRegression()
    model.fit(x_features_train, y_feature_train)

    # Predictions
    y_pred = model.predict(x_features_test)

    # Evaluate the model
    mse = mean_squared_error(y_feature_test, y_pred)
    r2 = r2_score(y_feature_test, y_pred)
    print(f"Mean Squared Error: {mse}")
    print(f"R^2 Score: {r2}")

    # Coefficients and Intercept
    print("Coefficients:", model.coef_)
    print("Intercept:", model.intercept_)

    # Visualization: Predicted vs Actual (since 3D plots aren't feasible)
    plt.scatter(y_feature_test, y_pred)
    plt.xlabel("Actual Values")
    plt.ylabel("Predicted Values")
    plt.title("Predicted vs Actual")
    plt.show()

    ###
    ### ========================================================================================
    ### ========================================================================================
    ###

    #model = train(x_features_train, y_feature_train)
    #plot_data_with_regression_line(x_features_test, model.weights, model.intercept)
    #plt.show()

#predicted_y_feature = model.predict(x_features_test)



    # mape = 0.0
    #
    # y_pred = model.predict(X_test)
    # mape = calculateMAPE(y_test, y_pred)
    #
    # print("MAPE: {:.2f}%".format(mape * 100))
    # plot_testing_data_with_predictions(X_test, y_test, y_pred)


if __name__ == "__main__":
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
