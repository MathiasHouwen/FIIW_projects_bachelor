import numpy as np
from sklearn.linear_model import LinearRegression
from src.ModelHandler import MLModel


class LinearRegressionModel(MLModel):

    def __init__(self):
        super().__init__()

        self.scikit_model = LinearRegression()


    def train(self, x_features: np.array, y_feature: np.array):

        self.scikit_model.fit(x_features, y_feature)


    def predict(self, x_features: np.array) -> np.array:

        return self.scikit_model.predict(x_features)