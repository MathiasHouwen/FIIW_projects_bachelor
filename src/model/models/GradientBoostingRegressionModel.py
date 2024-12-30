import numpy as np
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.model_selection import GridSearchCV

from src.model.ModelHandler import MLModel


class GradientBoostingRegressionModel(MLModel):

    def __init__(self):
        super().__init__()
        self.scikit_model =GradientBoostingRegressor(n_estimators=100, learning_rate=0.1, max_depth=3)


    def train(self, x_features: np.array, y_feature: np.array):

        self.scikit_model.fit(x_features, y_feature)



    def predict(self, x_features: np.array) -> np.array:

        return self.scikit_model.predict(x_features)