import numpy as np
import pandas as pd
from sklearn.metrics import mean_squared_error
from src.util.utils import split_actual_predicted_np_arr

def calculate_ape(actual:np.ndarray, predicted:np.ndarray) -> np.ndarray:
    return (abs(actual - predicted) / actual) * 100

def print_mean_square(dataframe: pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    mse = mean_squared_error(actual, predicted)
    print(f"Mean Squared Error: {mse}")

def print_MAPE(dataframe: pd.DataFrame, y_column_name:str):
    actual, predicted = split_actual_predicted_np_arr(dataframe, y_column_name)
    ape = calculate_ape(actual, predicted)
    mape = np.mean(ape)
    print(f"MAPE: {mape}%")
    return