#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Team names comma separated"
__version__ = "0.1.0"
__license__ = "GPLv3"

import argparse
import pandas as pd
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


def calculateMAPE(y_true, y_pred):
    """
    Calculate Mean Absolute Percentage Error (MAPE)
    """
    return mean_absolute_percentage_error(y_true, y_pred)


def main(args):
    """ Main entry point of the app """
    training_data = loadData(args.training_file)
    testing_data = loadData(args.testing_file)

    if training_data is None or testing_data is None:
        print("Failed to load the data.")
        return

    mape = 0.0

    print("MAPE: {}".format(mape))


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
