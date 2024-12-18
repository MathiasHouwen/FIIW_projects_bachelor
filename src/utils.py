
import pandas as pd


def split_features(df: pd.DataFrame, prediction_feature_name: str):
    y_feature = df[prediction_feature_name]
    x_features = df.loc[:, df.columns != prediction_feature_name]
    return x_features, y_feature
