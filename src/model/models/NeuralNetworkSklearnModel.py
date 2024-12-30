import numpy as np
from sklearn.neural_network import MLPRegressor
from src.model.ModelHandler import MLModel


class NeuralNetworkSklearnModel(MLModel):
    def __init__(self):
        super().__init__()

        # self.scikit_model = LinearRegression(fit_intercept=True)
        self.scikit_model = MLPRegressor(hidden_layer_sizes=(10, 10), max_iter=1000, random_state=42)

    def train(self, x_features: np.array, y_feature: np.array):
        self.scikit_model.fit(x_features, y_feature)

    def predict(self, x_features: np.array) -> np.array:
        return self.scikit_model.predict(x_features)
