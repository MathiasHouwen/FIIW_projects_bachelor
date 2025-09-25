import numpy as np
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.model_selection import GridSearchCV

from src.model.ModelHandler import MLModel


class GradientBoostingRegressionModel(MLModel):

    def __init__(self):
        super().__init__()
        self.param_grid = {
    'n_estimators': [100, 200],  # Number of boosting stages (reduce values)
    'learning_rate': [0.05, 0.1],  # Shrinkage rate (common effective values)
    'max_depth': [3, 5],  # Tree depth (simpler trees)
    'subsample': [0.8, 1.0]  # Fraction of samples for fitting each tree
}
        self.scikit_model = GradientBoostingRegressor()

    def train(self, x_features: np.array, y_feature: np.array):
        grid_search = GridSearchCV(
            estimator=self.scikit_model,
            param_grid=self.param_grid,
            scoring="neg_mean_squared_error",
            cv=2,
            n_jobs=-1,
            verbose=1
        )
        grid_search.fit(x_features, y_feature)
        print(f"Grid search Best Parameters: {grid_search.best_params_}")
        print(f"Grid search Best Score: {grid_search.best_score_}")
        self.scikit_model = grid_search.best_estimator_
        self.scikit_model.fit(x_features, y_feature)



    def predict(self, x_features: np.array) -> np.array:

        return self.scikit_model.predict(x_features)
