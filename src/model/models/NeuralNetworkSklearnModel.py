import numpy as np
from scipy.stats import uniform
from sklearn.model_selection import GridSearchCV, RandomizedSearchCV
from sklearn.neural_network import MLPRegressor
from src.model.ModelHandler import MLModel


class NeuralNetworkSklearnModel(MLModel):
    def __init__(self):
        super().__init__()

        param_grid = {
            'hidden_layer_sizes': [(10,), (10, 10), (32, 32)],
            'activation': ['relu', 'tanh'],
            'alpha': [0.0001, 0.001, 0.01],
            'learning_rate_init': [0.0001, 0.001],
            'solver': ['adam', 'sgd'],
            'max_iter': [1000, 2000]
        }

        self.param_dist = {
            'hidden_layer_sizes': [(10,), (10, 10), (32, 32)],
            'activation': ['relu', 'tanh'],
            'alpha': uniform(0.0001, 0.01),  # Random search across a continuous range
            'learning_rate_init': uniform(0.0001, 0.1),
            'solver': ['adam'],
            'max_iter': [500]  # Fewer iterations for faster convergence
        }

        self.scikit_model = MLPRegressor(random_state=42, early_stopping=True, n_iter_no_change=10)

    def train(self, x_features: np.array, y_feature: np.array):
        param_grid = self.param_grid
        param_dist = self.param_dist
        mlp = self.scikit_model

        # # Using RandomizedSearchCV for hyperparameter tuning
        # random_search = RandomizedSearchCV(mlp, param_distributions=param_dist,
        #                                    n_iter=50, cv=3, scoring='neg_mean_squared_error', n_jobs=-1,
        #                                    random_state=42)
        # random_search.fit(x_features, y_feature)

        # Using GridSearchCV for hyperparameter tuning
        grid_search = GridSearchCV(mlp, param_grid, cv=5, scoring='neg_mean_squared_error', n_jobs=-1)
        grid_search.fit(x_features, y_feature)

        # Find best model
        best_model = grid_search.best_estimator_
        # best_model = random_search.best_estimator_
        self.scikit_model = best_model

    def predict(self, x_features: np.array) -> np.array:
        return self.scikit_model.predict(x_features)
