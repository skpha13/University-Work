import numpy as np


def normalized_distances(x: np.ndarray):
    """Calculate the normalized distances from the origin for a given array of points.

    This function computes the distances of each point in the input array from the origin
    (0 for real numbers and magnitude for complex numbers). The distances are then normalized
    by dividing by the maximum distance.

    Args:
    x (np.ndarray): A NumPy array containing points, which can be either real or complex numbers.
    For real numbers, points will be provided in an array of lists like so:
        [[x1, y1], [x2, y2], ...]

    Returns:
    np.ndarray: A NumPy array of normalized distances from the origin.
                If the input array is empty, returns an empty array.
                If the maximum distance is zero, returns the original distances.
    """

    if len(x) == 0:
        return np.array([])

    if np.iscomplexobj(x):
        # For complex numbers, calculate the distance as the magnitude
        distances = np.abs(x)
    else:
        # For real numbers, calculate the euclidian distance
        distances = [np.linalg.norm(point, ord=2) for point in x]

    max_distance = np.max(distances)

    return distances / max_distance if max_distance != 0 else distances
