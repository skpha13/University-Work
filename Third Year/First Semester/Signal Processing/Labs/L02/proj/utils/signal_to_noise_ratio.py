import numpy as np


def find_gamma(x: np.ndarray, z: np.ndarray, SNR: float) -> float:
    """Calculates the gamma factor given input arrays x and z, and the Signal-to-Noise Ratio (SNR).

    Args:
        x (np.ndarray): The input array representing the signal.
        z (np.ndarray): The input array representing the noise.
        SNR (float): The Signal-to-Noise Ratio (SNR).

    Returns:
        float: The calculated gamma factor, based on the norms of x and z and the SNR.
    """
    x_norm = np.linalg.norm(x)
    z_norm = np.linalg.norm(z)

    return np.sqrt((x_norm / z_norm) / SNR)
