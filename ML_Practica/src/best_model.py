#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Ebbe Wertz, Robin Lambregts, Mathias Houwen"
__version__ = "2.0"
__license__ = "GPLv3"

# This file is a minimised abstraction from our code.
# For the full structured code, including multiple models, see the:
# 'full code' directory

import argparse

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from numpy.f2py import __version__
from sklearn.linear_model import LinearRegression

# =======================
# DATA MASSAGING
# =======================

def drop_date(dataframe):
    dataframe = dataframe.drop('Date', axis=1, inplace=False)
    return dataframe

def massage_for_linear_regression(train_df, test_df):
    train_df.dropna(inplace=True)
    test_df.dropna(inplace=True)
    train_df = drop_date(train_df)
    test_df = drop_date(test_df)
    return train_df, test_df

# =======================
# MODEL
# =======================

class LinearRegressionModel:

    def __init__(self):
        self.scikit_model = LinearRegression(fit_intercept=False)

    def train(self, x_features, y_feature):
        self.scikit_model.fit(x_features, y_feature)
        print(f"linear coefficients: {self.scikit_model.coef_}")
        print(f"linear intercept: {self.scikit_model.intercept_}")

    def predict(self, x_features):
        return self.scikit_model.predict(x_features)

# =======================
# UTILITY FUNCTIONS
# =======================

def df_to_np_arr(df):
    return np.array(df.values)

def split_actual_predicted_df(dataframe, y_column_name):
    actual = dataframe[y_column_name]
    predicted = dataframe[f"{y_column_name}_predicted"]
    return actual, predicted

def split_features(df, prediction_feature_name):
    y_feature = df[prediction_feature_name]
    x_features = df.loc[:, df.columns != prediction_feature_name]
    return x_features, y_feature

def split_actual_predicted_np_arr(dataframe, y_column_name):
    actual, predicted = split_actual_predicted_df(dataframe, y_column_name)
    return df_to_np_arr(actual), df_to_np_arr(predicted)

# =======================
# METRICS
# =======================

def calculate_ape(actual:np.ndarray, predicted:np.ndarray) -> np.ndarray:
    return (abs(actual - predicted) / actual) * 100

def print_MAPE(dataframe, y_column_name):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    ape = calculate_ape(actual, predicted)
    mape = np.mean(ape)
    print(f"MAPE: {mape}%")
    return

# =======================
# VISUALISATION
# =======================

def predicted_vs_actual_line(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_df(dataframe, y_column_name)
    plt.scatter(actual, predicted)
    plt.xlabel("Actual Values")
    plt.ylabel("Predicted Values")
    plt.grid()

def ape_boxplot(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    ape = calculate_ape(actual, predicted)
    plt.boxplot(ape)
    plt.grid()

# =======================
# MAIN
# =======================

def main(args):
    # read data from file
    training_dataframe = pd.read_csv(args.training_file)
    testing_dataframe = pd.read_csv(args.testing_file)
    # massage data
    training_dataframe, testing_dataframe = massage_for_linear_regression(training_dataframe, testing_dataframe)
    # model
    model = LinearRegressionModel()
    # TRAIN ================
    # extract features
    x_columns_train, y_column_train = split_features(training_dataframe, 'Last Close')
    # convert to numpy array
    x_cols_np_arr = df_to_np_arr(x_columns_train)
    y_col_np_arr = df_to_np_arr(y_column_train)
    # train
    model.train(x_cols_np_arr, y_col_np_arr)
    # PREDICT ===============
    # extract features
    x_columns_test, _ = split_features(testing_dataframe, 'Last Close')
    # convert to numpy array
    x_cols_np_arr = df_to_np_arr(x_columns_test)
    # predict
    predicted_y_column = model.predict(x_cols_np_arr)
    # store result
    testing_dataframe["Last Close_predicted"] = predicted_y_column

    print_MAPE(testing_dataframe, 'Last Close')
    plt.figure()
    predicted_vs_actual_line(testing_dataframe, 'Last Close')
    plt.figure()
    ape_boxplot(testing_dataframe, 'Last Close')
    plt.show()

if __name__ == "__main__":
    global args
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