from abc import ABC, abstractmethod

import numpy as np
from cvxopt import matrix
from l1regls import l1regls


class Selector(ABC):
    def __init__(self):
        self.s: int | None = None
        self.p: int | None = None
        self.m: int | None = None

        self.A: np.ndarray | None = None
        self.x: np.ndarray | None = None
        self.b: np.ndarray | None = None
        self.best_indices: list[int] = []

    def initialize(self, ar_sparse):
        self.s = ar_sparse.s
        self.p = ar_sparse.p
        self.m = ar_sparse.m

        self.A: np.ndarray | None = None
        self.x: np.ndarray | None = None
        self.b = ar_sparse.b
        self.best_indices: list[int] = []

    @abstractmethod
    def select(self, candidate_regressors: np.ndarray) -> tuple[np.ndarray | None, np.ndarray, list[int] | None]:
        pass


class GreedySelector(Selector):
    def select(self, candidate_regressors: np.ndarray) -> tuple[np.ndarray | None, np.ndarray, list[int] | None]:
        self.A = np.empty((self.m, 0))

        for step in range(self.s):
            best_index = -1
            best_residual = np.inf
            for i in range(self.p):
                if i in self.best_indices:
                    continue

                A = np.column_stack((self.A, candidate_regressors[:, i]))
                x, _, _, _ = np.linalg.lstsq(A, self.b)

                residual = self.b - A @ x
                residual = np.sum(np.square(residual))

                if residual < best_residual:
                    best_index = i
                    best_residual = residual

            if best_index == -1:
                raise RuntimeError(f"No index found at step: {step}.")

            self.A = np.column_stack((self.A, candidate_regressors[:, best_index]))
            self.best_indices.append(best_index)
            self.x, _, _, _ = np.linalg.lstsq(self.A, self.b)

        return self.A, self.x, self.best_indices


class L1Selector(Selector):
    def __init__(self, alpha: float = 0.01):
        super().__init__()
        self.alpha = alpha

    def select(self, candidate_regressors: np.ndarray) -> tuple[np.ndarray | None, np.ndarray, list[int] | None]:
        # method from:
        # https://cvxopt.org/examples/mlbook/l1regls.html

        A_cvxopt = matrix(candidate_regressors)
        b_cvxopt = matrix(self.b)

        x_cvxopt = l1regls(A_cvxopt, b_cvxopt)
        x = np.array(x_cvxopt).flatten()

        # select top m indices to have x the same shape as b
        # for m = 2 and p = 3, x would be of shape 3 and be of shape 2, which would not work with our predict as it computes x * b
        x_sorted = np.argsort(x)
        selected_x_indices = x_sorted[-self.m :]

        return np.array(candidate_regressors[:, selected_x_indices]), x[selected_x_indices], selected_x_indices.tolist()
