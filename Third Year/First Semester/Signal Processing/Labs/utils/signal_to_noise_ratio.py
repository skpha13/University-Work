from typing import Literal

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


def compute_snr_of_image(original: np.ndarray, noisy: np.ndarray, method: Literal["MS", "STD", "FFT"] = "STD") -> float:
    """Computes the Signal-to-Noise Ratio (SNR) of an image.

    Args:
        original (np.ndarray): The original image array (signal).
        noisy (np.ndarray): The noisy image array.
        method (Literal["MS", "STD", "FFT"], optional): The method used to calculate SNR.
            - "MS": Mean Squared based SNR.
            - "STD": Standard Deviation based SNR.
            - "FFT": Frequency domain SNR using Fast Fourier Transform.
            Default is "FFT".

    Returns:
        float: The SNR of the image
    """

    if method == "MS":
        signal_power = np.mean(np.power(np.abs(original), 2))
        noise_power = np.mean(np.power(np.abs(noisy - original), 2))

        return 10 * np.log10(signal_power / noise_power)

    if method == "STD":
        return 10 * np.log10(np.mean(noisy) ** 2 / np.std(noisy) ** 2)

    if method == "FFT":
        fft = np.fft.fft2(original)
        signal_power = np.sum(np.abs(fft) ** 2)

        fft = np.fft.fft2(noisy)
        noise_power = np.sum(np.abs(fft) ** 2)

        return signal_power / noise_power
