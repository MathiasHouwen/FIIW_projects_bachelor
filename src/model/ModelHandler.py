import numpy as np
from abc import ABC, abstractmethod
from typing import Callable, Type, TypeVar, Generic, Optional
import pandas as pd

from src.util.utils import split_features

# ABC = ABstract Class
class MLModel(ABC):
    def __init__(self):
        self._model = None
    @abstractmethod
    def train(self, x_features: np.array, y_feature: np.array): pass
    @abstractmethod
    def predict(self, x_features: np.array) -> np.array: pass



T = TypeVar('T',bound=MLModel)



class ModelHandler(Generic[T]):
    def __init__(self,
                 test_dataframe:pd.DataFrame,
                 train_dataframe:pd.DataFrame,
                 y_column:str,
                 model_class: Type[T],
                 massaging_function: Optional[Callable[[pd.DataFrame], pd.DataFrame]] = None):

        self._test_dataframe = test_dataframe
        self._train_dataframe = train_dataframe
        self._y_column_name = y_column
        self._massaging_function = massaging_function
        self._model = model_class()


    def massage(self):

        if self._massaging_function is None:
            return

        self._train_dataframe = self._massaging_function(self._train_dataframe)
        self._test_dataframe = self._massaging_function(self._test_dataframe)


    def train(self):
        """Applies pre massaging and trains the model"""

        # extract columns
        x_columns_train, y_column_train = split_features(self._train_dataframe, self._y_column_name)

        # convert to numpy array
        x_cols_np_arr = np.array(x_columns_train.values)
        y_col_np_arr = np.array(y_column_train.values)

        # train
        self._model.train(x_cols_np_arr, y_col_np_arr)


    def predict(self):
        """predicts data and post massages it"""

        # extract columns
        x_columns_test, _ = split_features(self._test_dataframe, self._y_column_name)

        # predict
        # convert to numpy array
        x_cols_np_arr = np.array(x_columns_test.values)
        predicted_y_column = self._model.predict(x_cols_np_arr)

        # store result
        self._test_dataframe[f"{self._y_column_name}_predicted"] = predicted_y_column


    def getTestDataframe(self):
        return self._test_dataframe