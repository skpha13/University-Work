from copy import deepcopy

import numpy as np


def gaussian_elimination(matrix: np.ndarray, b: np.ndarray) -> np.ndarray:
    """Performs Gaussian elimination on a matrix to reduce it to upper triangular form.

    Args:
        matrix (np.ndarray): The matrix to be transformed, where each row represents a system equation.
        b (np.ndarray): The vector of constants corresponding to the system equations.

    Returns:
        np.ndarray: The upper triangular form of the input matrix after applying Gaussian elimination.
    """
    n = len(matrix)
    matrix_copy = deepcopy(matrix)
    for k in range(0, n - 1):
        for i in range(k + 1, n):
            # Calculeaza multiplicatorii Gaussieni
            matrix_copy[i][k] = -matrix_copy[i][k] / matrix_copy[k][k]  # Se suprascriu in triunghiul inferior
            b[i] = b[i] + b[k] * matrix_copy[i][k]  # Transformarea termenului liber
            # Aplica multiplicatorii
            for j in range(k + 1, n):
                matrix_copy[i][j] = matrix_copy[i][j] + matrix_copy[k][j] * matrix_copy[i][k]

    return np.triu(matrix_copy)


def UTRIS(L: np.ndarray, b: np.ndarray) -> np.ndarray:
    """Solves an upper triangular matrix system using back-substitution.

    Args:
        L (np.ndarray): The upper triangular matrix, where each row represents a system equation.
        b (np.ndarray): The vector of constants after Gaussian elimination.

    Returns:
        np.ndarray: Solution vector `x` of the system.
    """
    n = len(L) - 1
    x = b
    for i in range(n, -1, -1):
        for j in range(0, n - i):
            x[i] = x[i] - L[i][n - j] * x[j]
        x[i] = x[i] / L[i][i]

    return x


def gaussian_elimination_hessenberg(matrix: np.ndarray) -> np.ndarray:
    """Performs Gaussian elimination on an upper Hessenberg matrix to reduce it to upper triangular form.

    Args:
        matrix (np.ndarray): The matrix to be transformed, where each row represents a system equation.

    Returns:
        np.ndarray: The upper triangular form of the input matrix after applying Gaussian elimination.
    """
    n = len(matrix)
    a = deepcopy(matrix)
    for k in range(0, n - 1):
        a[k + 1][k] = -a[k + 1][k] / a[k][k]

        for i in range(k + 1, n):
            a[k + 1][i] = a[k + 1][i] + a[k][i] * (a[k + 1][k] / a[k][k])

    return np.triu(a)


def gaussian_elimination_upper_matrix(matrix: np.ndarray) -> np.ndarray:
    """Performs Gaussian elimination on an upper matrix with one not null line to reduce it to upper triangular form.

    Args:
        matrix (np.ndarray): The matrix to be transformed, where each row represents a system equation.

    Returns:
        np.ndarray: The upper triangular form of the input matrix after applying Gaussian elimination.
    """
    n = len(matrix)
    a = deepcopy(matrix)
    for k in range(0, n - 1):
        a[n - 1][k] = -a[n - 1][k] / a[k][k]

        for i in range(k + 1, n):
            a[n - 1][i] = a[n - 1][i] + a[k][i] * (a[n - 1][k] / a[k][k])

    return np.triu(a)
