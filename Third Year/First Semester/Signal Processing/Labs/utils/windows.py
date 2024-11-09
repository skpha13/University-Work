import numpy as np


def rectangle_window(Nw: int) -> np.ndarray:
    return np.array([1 for i in range(Nw)])


def hanning_window(Nw: int) -> np.ndarray:
    return np.array([0.5 * (1 - np.cos(2 * np.pi * i / Nw)) for i in range(Nw)])
