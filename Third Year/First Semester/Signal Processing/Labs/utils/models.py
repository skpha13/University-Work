from abc import ABC, abstractmethod
from typing import Literal

import numpy as np

from utils.sparse_selection import L1, GreedySelector, Selector


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

    def _validate_attribute(self, attribute_name: str):
        if getattr(self, attribute_name) is None:
            raise ValueError(
                f"Prediction error: Model {attribute_name} values are not initialized. "
                "Ensure that 'fit()' has been called with appropriate data before prediction."
            )


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


class MA(Model):
    def __init__(self, q: int):
        self.A: np.ndarray | None = None
        self.b: np.ndarray | None = None
        self.thetas: np.ndarray | None = None
        self.residuals: np.ndarray | None = None
        self.rank: int | None = None
        self.s: np.ndarray | None = None

        self.q = q
        self.mean: int = 0

    def fit(self, series: np.ndarray):
        self.mean = np.mean(series)
        series = series - self.mean
        m = len(series) - self.q

        A = []
        self.b = series[self.q :]

        e = np.concatenate(([self.mean], np.random.normal(0, 1, size=len(series))))
        for i in range(0, m):
            A.append(e[i : i + self.q])

        self.A = np.array(A)
        self.thetas, self.residuals, self.rank, self.s = np.linalg.lstsq(A, self.b)

    def predict(self) -> np.float64:
        return self.mean + np.dot(self.thetas, self.b[-len(self.thetas) :])

    def mse(self) -> np.float64:
        return self.residuals[0]


class AR(Model):
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
        self._validate_attribute("x")
        self._validate_attribute("b")

        p = len(self.x)
        return np.dot(self.x, self.b[-p:])


class ARMA(Model):
    """Implements an Auto-Regressive Moving Average (ARMA) model for time series prediction."""

    def __init__(self, p: int, q: int):
        self.p = p
        self.q = q

        self.ar = AR(p, q)
        self.ma = MA(q)

        self.mean = 0

    def fit(self, series: np.ndarray):
        self.mean = np.mean(series)

        self.ar.fit(series)
        self.ma.fit(series)

    def predict(self):
        ar_prediction = self.ar.predict()
        ma_prediction = self.ma.predict()
        return ar_prediction + ma_prediction - self.mean


class ARSparse(Model):
    """Implements the AR model using sparse representation."""

    def __init__(self, p: int, m: int, s: int, selector: Literal["greedy", "l1"] = "greedy"):
        self.A: np.ndarray | None = None
        self.b: np.ndarray | None = None
        self.x: np.ndarray | None = None
        self.best_indices: list[int] = []

        self.p: int = p
        self.m: int = m
        self.s: int = s

        self.selectors: dict[str, Selector] = {"greedy": GreedySelector(), "l1": L1()}
        self.selector: Selector = self.selectors[selector]

    def fit(self, series: np.ndarray):
        if self.s > self.m:
            raise ValueError("Number of columns selected should be lower then the number of constraints. (s > m)")

        candidate_regressors = []
        self.b = series[-self.m :]

        for i in range(self.m, 0, -1):
            index = len(series) - i
            candidate_regressors.append(series[index - self.p : index])

        candidate_regressors = np.array(candidate_regressors)
        self.selector.initialize(self)
        self.A, self.x, self.best_indices = self.selector.select(candidate_regressors)

    def predict(self):
        self._validate_attribute("A")
        self._validate_attribute("x")
        self._validate_attribute("b")

        return np.dot(self.b[-self.s :], self.x)
