import pandas as pd


def pre_massage(df: pd.DataFrame):
    df = df.drop('Date', axis=1, inplace=False)
    return df