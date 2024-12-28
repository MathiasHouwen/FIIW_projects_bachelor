import pandas as pd
from sklearn.metrics import mean_squared_error
from src.util.utils import split_actual_predicted_np_arr


def print_mean_square(dataframe: pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    mse = mean_squared_error(actual, predicted)
    print(f"Mean Squared Error: {mse}")
