from abc import ABC, abstractmethod

import numpy as np


class Selector(ABC):
    @abstractmethod
    def initialize(self, ar_sparse):
        pass

    @abstractmethod
    def select(self, candidate_regressors: np.ndarray):
        pass


class GreedySelector(Selector):
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

    def select(self, candidate_regressors: np.ndarray) -> tuple[np.ndarray, np.ndarray, list[int]]:
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


class L1(Selector):
    def __init__(self):
        pass

    def initialize(self, ar_sparse):
        pass

    def select(self, candidate_regressors: np.ndarray):
        pass
