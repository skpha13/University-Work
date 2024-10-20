import numpy as np


def normalized_distances(x: np.ndarray):
    if len(x) == 0:
        return np.array([])

    if np.iscomplexobj(x):
        # For complex numbers, calculate the distance as the magnitude
        distances = np.abs(x)
    else:
        # For real numbers, calculate the absolute values
        distances = np.linalg.norm(x, ord=2)

    max_distance = np.max(distances)

    return distances / max_distance if max_distance != 0 else distances
