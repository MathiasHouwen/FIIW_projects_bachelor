import argparse
from argparse import Namespace

import pandas as pd


def split_features(df: pd.DataFrame, prediction_feature_name: str) -> tuple[pd.DataFrame, pd.DataFrame]:
    y_feature = df[prediction_feature_name]
    x_features = df.loc[:, df.columns != prediction_feature_name]
    return x_features, y_feature

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