import numpy as np


def power_method(A: np.ndarray, max_iterations: int = 1000):
    tolerance = 1e-6
    error = 1
    iterations = 0

    y = np.random.rand(len(A))
    y = np.divide(y, np.linalg.norm(y))

    while error > tolerance:
        if iterations > max_iterations:
            break

        z = np.dot(A, y)
        z = np.divide(z, np.linalg.norm(z))

        error = np.linalg.norm(z - y)

        y = z
        iterations += 1

    eigen_value = np.dot(y, np.dot(A, y)) / np.dot(y, y)
    return y, eigen_value
