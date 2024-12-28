import argparse
from argparse import Namespace

import numpy as np
import pandas as pd


def split_features(df: pd.DataFrame, prediction_feature_name: str) -> tuple[pd.DataFrame, pd.DataFrame]:
    y_feature = df[prediction_feature_name]
    x_features = df.loc[:, df.columns != prediction_feature_name]
    return x_features, y_feature

def split_actual_predicted_df(dataframe:pd.DataFrame, y_column_name:str) -> tuple[pd.DataFrame, pd.DataFrame]:
    actual = dataframe[y_column_name]
    predicted = dataframe[f"{y_column_name}_predicted"]
    return actual, predicted

def split_actual_predicted_np_arr(dataframe:pd.DataFrame, y_column_name:str) -> tuple[np.ndarray, np.ndarray]:
    actual, predicted = split_actual_predicted_df(dataframe, y_column_name)
    return df_to_np_arr(actual), df_to_np_arr(predicted)

def df_to_np_arr(df: pd.DataFrame) -> np.ndarray:
    return np.array(df.values)

def make_parser_and_parse(version:str) -> Namespace:
    parser = argparse.ArgumentParser()
    # Required positional argument
    parser.add_argument("training_file", help="Training data file")
    parser.add_argument("testing_file", help="Testing data file")
    # Specify output of "--version"
    parser.add_argument(
        "--version",
        action="version",
        version="%(prog)s (version {version})".format(version=version))
    return parser.parse_args()