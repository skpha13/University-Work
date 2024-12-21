import numpy as np


def get_roots(polynom: np.ndarray | list) -> np.ndarray:
    """Compute the roots of a polynomial using its companion matrix.

    Args:
        polynom (np.ndarray | list): Coefficients of the polynomial, in order of the highest power to the lowest power.
                                     For example, for the polynomial: x^2 + 2x - 1,
                                     the input should be [1, 2, -1].

    Returns:
        np.ndarray: An array of the roots of the polynomial.

    Note:
        The coefficients should be provided in descending order of powers of the variable.
    """

    n = len(polynom) - 1
    companion_matrix = np.zeros((n, n))

    for i in range(1, n):
        companion_matrix[i][i - 1] = 1

    for i in range(n):
        companion_matrix[i][n - 1] = -polynom[n - i]

    roots = np.linalg.eigvals(companion_matrix)
    return roots
