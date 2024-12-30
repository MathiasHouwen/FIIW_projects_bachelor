import numpy as np
from sklearn.model_selection import GridSearchCV
from sklearn.neural_network import MLPRegressor
from src.model.ModelHandler import MLModel


class NeuralNetworkSklearnModel(MLModel):
    def __init__(self):
        super().__init__()

        self.param_grid = {
            'hidden_layer_sizes': [(10, 10), (32, 32), (64, 64, 32)],
            'activation': ['relu', 'tanh'],
            'alpha': [0.0001, 0.001, 0.01],  # Regularization term
            'learning_rate_init': [0.001, 0.01, 0.1],  # Initial learning rate
            'max_iter': [500, 1000]
        }

        self.scikit_model = MLPRegressor(random_state=42, verbose=True)

    def train(self, x_features: np.array, y_feature: np.array):
        param_grid = self.param_grid
        mlp = self.scikit_model

        # Using GridSearchCV for hyperparameter tuning
        grid_search = GridSearchCV(mlp, param_grid, cv=5, scoring='neg_mean_squared_error', n_jobs=-1)
        grid_search.fit(x_features, y_feature)

        # Find best model
        best_model = grid_search.best_estimator_
        self.scikit_model = best_model

    def predict(self, x_features: np.array) -> np.array:
        return self.scikit_model.predict(x_features)
