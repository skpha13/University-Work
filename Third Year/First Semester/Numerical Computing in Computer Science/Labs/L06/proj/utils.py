import numpy as np


def my_pdf(xs: list[float], mean: float, sigma: float) -> list[float]:
    result: list[float] = []

    for x in xs:
        result.append(1 / np.sqrt(2 * np.pi * sigma**2) * np.exp((-1 * (x - mean) ** 2) / (2 * sigma**2)))

    return result
