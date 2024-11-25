from abc import ABC, abstractmethod

import numpy as np


class Model(ABC):
    """Abstract base class for models.

    Provides a template for implementing `fit` and `predict` methods.
    Subclasses must override these methods.
    """

    @abstractmethod
    def fit(self):
        raise NotImplementedError("Subclasses must implement the 'fit' method.")

    @abstractmethod
    def predict(self):
        raise NotImplementedError("Subclasses must implement the 'predict' method.")


class ARModel:
    """Implements an Auto-Regressive (AR) model for time series prediction."""

    def __init__(self) -> None:
        """Initializes an ARModel instance with default attributes set to None."""

        self.A: np.ndarray | None = None
        self.b: np.ndarray | None = None
        self.x: np.ndarray | None = None
        self.residuals: np.ndarray | None = None
        self.rank: int | None = None
        self.s: np.ndarray | None = None

    def fit(self, series: np.ndarray, p: int, m: int) -> None:
        """Fits the AR model to a given time series.

        Args:
            series (np.ndarray): The time series data as a 1D NumPy array.
            p (int): The dimension of the AR model (number of lags).
            m (int): The number of points in the prediction horizon.

        Raises:
            ValueError: If the time horizon (`m`) is smaller than the AR model dimension (`p`).
        """

        if m < p:
            raise ValueError(
                f"Invalid configuration: Time horizon (m={m}) cannot be smaller than "
                f"the dimension of AR (p={p}). Ensure m >= p."
            )

        A = []
        self.b = series[-m:]

        for i in range(m, 0, -1):
            index = len(series) - i - 1
            A.append(series[index - p + 1 : index + 1])

        self.A = np.array(A)
        self.x, self.residuals, self.rank, self.s = np.linalg.lstsq(A, self.b)

    def predict(self) -> np.float64:
        """Predicts the next value in the time series based on the fitted AR model.

        Returns:
            np.float64: The predicted value.

        Raises:
            ValueError: If the model coefficients (`x`) are not initialized.
            ValueError: If the expected values (`b`) are not loaded.
        """

        if self.x is None:
            raise ValueError(
                "Prediction error: Model coefficients are not initialized. "
                "Ensure that 'fit()' has been called with appropriate data before prediction."
            )

        if self.b is None:
            raise ValueError(
                "Prediction error: Expected values (b) are not initialized. "
                "Ensure that 'fit()' has been called with appropriate data before prediction."
            )

        p = len(self.x)
        return np.dot(self.x, self.b[-p:])

    def mse(self) -> np.float64:
        np.sum(np.power(self.residuals, 2)) / len(self.residuals)
