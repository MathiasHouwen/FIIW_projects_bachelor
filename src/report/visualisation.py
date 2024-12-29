import pandas as pd
from matplotlib import pyplot as plt

from src.report.metrics import calculate_ape
from src.util.utils import split_actual_predicted_df, split_actual_predicted_np_arr


def predicted_vs_actual_line(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_df(dataframe, y_column_name)
    plt.scatter(actual, predicted)
    plt.xlabel("Actual Values")
    plt.ylabel("Predicted Values")
    plt.title("Predicted vs Actual")

def ape_boxplot(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    ape = calculate_ape(actual, predicted)
    plt.boxplot(ape)
    plt.title("Absolute Percentage Error")