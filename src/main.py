#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Team names comma separated"
__version__ = "0.1.0"
__license__ = "GPLv3"

import pandas as pd
import argparse



from src.models import train
from src.pre_massaging import pre_massage
from src.utils import split_features




def calculateMAPE(y_true, y_pred):
    """
    Calculate Mean Absolute Percentage Error (MAPE)
    """
    return mean_absolute_percentage_error(y_true, y_pred)





def main(args):
    """ Main entry point of the app """
    training_data = pd.read_csv(args.training_file)
    testing_data = pd.read_csv(args.testing_file)

    training_data = pre_massage(training_data)
    testing_data = pre_massage(testing_data)

    x_features_train, y_feature_train = split_features(training_data, 'Last Close')
    x_features_test, _ = split_features(testing_data, 'Last Close')

    model = train(x_features_train, y_feature_train)
    print(model.weights)
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
