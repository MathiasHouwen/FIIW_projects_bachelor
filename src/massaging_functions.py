import pandas as pd

def drop_date(dataframe: pd.DataFrame) -> pd.DataFrame:
    dataframe = dataframe.drop('Date', axis=1, inplace=False)
    return dataframe

def massage_for_linear_regression(dataframe: pd.DataFrame) -> pd.DataFrame:
    dataframe = drop_date(dataframe)
    return dataframe

def massage_for_neural_network(dataframe: pd.DataFrame) -> pd.DataFrame:
    dataframe = drop_date(dataframe)
    return dataframe
