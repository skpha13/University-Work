from typing import Callable

import numpy as np


def compute_image(shape: tuple[int, int], f: Callable[[int, int], float], norm: bool = False) -> np.ndarray:
    eps = 1e-9
    matrix = np.zeros(shape)

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix[i][j] = f(i, j)

    if norm:
        return np.abs(10 * np.log10(np.abs(matrix) + eps))

    return matrix
