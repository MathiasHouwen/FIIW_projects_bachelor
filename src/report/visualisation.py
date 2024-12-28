import pandas as pd
from matplotlib import pyplot as plt

def predicted_vs_actual_line(dataframe:pd.DataFrame, y_column_name:str):
    actual = dataframe[y_column_name]
    predicted = dataframe[f"{y_column_name}_predicted"]
    plt.scatter(actual, predicted)
    plt.xlabel("Actual Values")
    plt.ylabel("Predicted Values")
    plt.title("Predicted vs Actual")