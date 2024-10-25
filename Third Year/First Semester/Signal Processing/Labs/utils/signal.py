import numpy as np


def segment_signal(signal: np.ndarray) -> np.ndarray:
    """Segments the input signal into overlapping windows.

    Args:
        signal (np.ndarray): The input 1D array representing the signal to be segmented.

    Returns:
        np.ndarray: A 2D array where each row represents a windowed segment of the original signal.

    Notes:
        - Each segment is of length `window_size`, defined as 1% of the signal length.
        - Segments overlap by half of `window_size`.
    """
    segmented_signal = []
    window_size = len(signal) // 100
    step = window_size // 2

    for i in range(0, len(signal) - window_size + 1, step):
        segmented_signal.append(signal[i : i + window_size])

    return np.array(segmented_signal)
