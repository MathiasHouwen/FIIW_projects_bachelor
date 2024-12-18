import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_percentage_error

class LinearRegressionModel:
    def __init__(self, x_features_df:pd.DataFrame, y_feature_df:pd.DataFrame):
        self.weights = None
        self.intercept = None
        self.scikit_model = LinearRegression()
        self.x_features_np_array = np.array(x_features_df.values)
        self.y_feature_np_array = np.array(y_feature_df.values)
    def train(self):
        self.scikit_model.fit(self.x_features_np_array, self.y_feature_np_array)
        self.weights = self.scikit_model.coef_
        self.intercept = self.scikit_model.intercept_
        print(self.weights, self.intercept)
    def predict(self, x_features: pd.DataFrame):
        return None

def train(x_features: pd.DataFrame, y_feature: pd.DataFrame):
    model = LinearRegressionModel(x_features, y_feature)
    model.train()
    return model
