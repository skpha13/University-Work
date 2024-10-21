import numpy as np


def sinusoidal_signal(A: float = 1, f: float = 1, t: float = 1, phi: float = 0, n: int = 100) -> np.ndarray:
    """Generates a sinusoidal signal based on the given parameters.

    Args:
        A (float, optional): Amplitude of the signal. Default is 1.
        f (float, optional): Frequency of the signal in Hz. Default is 1 Hz.
        t (float, optional): Duration of the signal in seconds. Default is 1 second.
        phi (float, optional): Phase offset in radians. Default is 0.
        n (int, optional): Number of sample points. Default is 100.

    Returns:
        np.ndarray: A numpy array representing the sinusoidal signal over the specified time duration.
    """
    nts = np.linspace(0, t, n)
    return A * np.sin(2 * np.pi * f * nts + phi)


def cosinus_signal(A: float = 1, f: float = 1, t: float = 1, phi: float = 0, n: int = 100) -> np.ndarray:
    """Generates a cosinus signal based on the given parameters.

    Args:
        A (float, optional): Amplitude of the signal. Default is 1.
        f (float, optional): Frequency of the signal in Hz. Default is 1 Hz.
        t (float, optional): Duration of the signal in seconds. Default is 1 second.
        phi (float, optional): Phase offset in radians. Default is 0.
        n (int, optional): Number of sample points. Default is 100.

    Returns:
        np.ndarray: A numpy array representing the cosinus signal over the specified time duration.
    """
    nts = np.linspace(0, t, n)
    return A * np.cos(2 * np.pi * f * nts + phi)
