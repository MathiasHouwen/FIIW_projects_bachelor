from typing import Tuple

import pandas as pd
from sklearn.preprocessing import StandardScaler
from src.util.utils import split_features, df_to_np_arr


def drop_date(dataframe: pd.DataFrame) -> pd.DataFrame:
    dataframe = dataframe.drop('Date', axis=1, inplace=False)
    return dataframe

def include_lagged_features(dataframe: pd.DataFrame) -> pd.DataFrame:
    column_names = dataframe.columns
    column_names_lag = [f"previous_{col}" for col in column_names]
    dataframe[column_names_lag] = dataframe[column_names].shift(1)
    dataframe.dropna(inplace=True) # there will be one empty cell after shifting
    return dataframe

def include_diff_features(dataframe: pd.DataFrame) -> pd.DataFrame:
    x_columns, _ = split_features(dataframe, 'Last Close')
    column_names = x_columns.columns
    column_names_diff = [f"diff_{col}" for col in column_names]
    dataframe[column_names_diff] = dataframe[column_names].diff()
    dataframe.dropna(inplace=True) # there will be one empty cell after shifting
    return dataframe

def include_lagged_and_diff(dataframe: pd.DataFrame) -> pd.DataFrame:
    x_columns, _ = split_features(dataframe, 'Last Close')
    column_names = x_columns.columns
    column_names_lag = [f"diff_{col}" for col in column_names]
    column_names_diff = [f"previous_{col}" for col in column_names]
    dataframe[column_names_lag] = dataframe[column_names].shift(1)
    dataframe[column_names_diff] = dataframe[column_names].diff()
    dataframe.dropna(inplace=True) # there will be one empty cell after shifting
    return dataframe










def massage_for_linear_regression(train_df: pd.DataFrame, test_df: pd.DataFrame) -> Tuple[pd.DataFrame, pd.DataFrame]:
    train_df.dropna(inplace=True)
    test_df.dropna(inplace=True)
    train_df = drop_date(train_df)
    test_df = drop_date(test_df)

    # train_df = include_diff_features(train_df)
    # test_df = include_diff_features(test_df)

    return train_df, test_df

def massage_for_grad_boost(train_df: pd.DataFrame, test_df: pd.DataFrame) -> Tuple[pd.DataFrame, pd.DataFrame]:
    train_df.dropna(inplace=True)
    test_df.dropna(inplace=True)
    train_df = drop_date(train_df)
    test_df = drop_date(test_df)

    # train_df = include_lagged_features(train_df)
    # test_df = include_lagged_features(test_df)

    x_columns_train, _ = split_features(train_df, 'Last Close')
    x_columns_test, _ = split_features(test_df, 'Last Close')

    scaler = StandardScaler()
    x_train_scaled = scaler.fit_transform(x_columns_train)
    x_test_scaled = scaler.transform(x_columns_test)

    train_df[x_columns_train.columns] = x_train_scaled
    test_df[x_columns_train.columns] = x_test_scaled

    return train_df, test_df

def massage_for_neural_network(train_df: pd.DataFrame, test_df: pd.DataFrame) -> Tuple[pd.DataFrame, pd.DataFrame]:
    train_df.dropna(inplace=True)
    test_df.dropna(inplace=True)
    train_df = drop_date(train_df)
    test_df = drop_date(test_df)

    return train_df, test_df
