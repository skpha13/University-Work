from abc import ABC, abstractmethod

import numpy as np


class Model(ABC):
    """Abstract base class for models.

    Provides a template for implementing `fit` and `predict` methods.
    Subclasses must override these methods.
    """

    @abstractmethod
    def fit(self, series: np.ndarray):
        raise NotImplementedError("Subclasses must implement the 'fit' method.")

    @abstractmethod
    def predict(self):
        raise NotImplementedError("Subclasses must implement the 'predict' method.")


class EMA(Model):
    """Implements an exponential moving average (EMA) model for time series prediction."""

    def __init__(self, alpha: float) -> None:
        self.alpha = np.clip([alpha], 0, 1)[0]

    def fit(self, series: np.ndarray) -> np.ndarray:
        s = np.zeros(len(series)).astype(np.float64)
        s[0] = series[0]

        for t in range(1, len(series)):
            s[t] = self.alpha * series[t] + (1 - self.alpha) * s[t - 1]

        return s

    def predict(self):
        raise NotImplementedError("EMA Model does not need a predict implementation")


class ARModel(Model):
    """Implements an Auto-Regressive (AR) model for time series prediction.

    Attributes:
        p (int): The dimension of the AR model (number of lags).
        m (int): The number of points in the prediction horizon.
    """

    def __init__(self, p: int, m: int) -> None:
        """Initializes an ARModel instance with default attributes set to None."""

        self.A: np.ndarray | None = None
        self.b: np.ndarray | None = None
        self.x: np.ndarray | None = None
        self.residuals: np.ndarray | None = None
        self.rank: int | None = None
        self.s: np.ndarray | None = None

        self.p: int = p
        self.m: int = m

    def fit(self, series: np.ndarray) -> None:
        """Fits the AR model to a given time series.

        Args:
            series (np.ndarray): The time series data as a 1D NumPy array.

        Raises:
            ValueError: If the time horizon (`m`) is smaller than the AR model dimension (`p`).
        """

        if self.m < self.p:
            raise ValueError(
                f"Invalid configuration: Time horizon (m={self.m}) cannot be smaller than "
                f"the dimension of AR (p={self.p}). Ensure m >= p."
            )

        A = []
        self.b = series[-self.m :]

        for i in range(self.m, 0, -1):
            index = len(series) - i
            A.append(series[index - self.p : index])

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
