import numpy as np
from sklearn.linear_model import LinearRegression
from src.model.ModelHandler import MLModel


class LinearRegressionModel(MLModel):

    def __init__(self):
        super().__init__()

        #self.scikit_model = LinearRegression(fit_intercept=True)
        self.scikit_model = LinearRegression(fit_intercept=False)


    def train(self, x_features: np.array, y_feature: np.array):

        self.scikit_model.fit(x_features, y_feature)
        print(f"linear coefficients: {self.scikit_model.coef_}")
        print(f"linear intercept: {self.scikit_model.intercept_}")


    def predict(self, x_features: np.array) -> np.array:

        return self.scikit_model.predict(x_features)