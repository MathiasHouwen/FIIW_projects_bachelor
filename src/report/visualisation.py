import pandas as pd
from matplotlib import pyplot as plt

from src.util.utils import split_actual_predicted_df


def predicted_vs_actual_line(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_df(dataframe, y_column_name)
    plt.scatter(actual, predicted)
    plt.xlabel("Actual Values")
    plt.ylabel("Predicted Values")
    plt.title("Predicted vs Actual")