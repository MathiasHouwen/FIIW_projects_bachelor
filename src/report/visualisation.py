import pandas as pd
from matplotlib import pyplot as plt

from src.report.metrics import calculate_ape
from src.util.utils import split_actual_predicted_df, split_actual_predicted_np_arr, split_features


def predicted_vs_actual_line(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_df(dataframe, y_column_name)
    plt.scatter(actual, predicted)
    plt.xlabel("Actual Values")
    plt.ylabel("Predicted Values")
    plt.grid()
    plt.title("Predicted vs Actual")

def ape_boxplot(dataframe:pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    ape = calculate_ape(actual, predicted)
    plt.boxplot(ape)
    plt.grid()
    plt.title("Absolute Percentage Error")

def plot_input_data(dataframe:pd.DataFrame, y_column_name:str):
    x_columns, y_column = split_features(dataframe, y_column_name)
    x_columns = x_columns.drop('Date', axis=1, inplace=False)

    for i, x_column_name in enumerate(x_columns.columns):
        plt.subplot(3, 1, i + 1)
        plt.scatter(y_column, x_columns[x_column_name])
        plt.title(f"{x_column_name} vs {y_column_name}")
        plt.xlabel(y_column_name)
        plt.ylabel(x_column_name)
        plt.grid()

    plt.tight_layout()