import numpy as np
from matplotlib import pyplot as plt


class SignalAnalyzer:
    """A utility class for analyzing signals using Fast Fourier Transform (FFT)."""

    @staticmethod
    def compute_fft_frequency_magnitude(signal: np.ndarray, sample_rate: float | None = None):
        """Computes the FFT of a signal and returns the frequencies and their magnitudes.

        Args:
            signal (np.ndarray): The input signal as a 1D numpy array.
            sample_rate (float | None, optional): The sample rate of the signal.
                If provided, the frequencies array is computed; otherwise, it is set to None.

        Returns:
            tuple: (fft_values, frequencies, magnitude), where:
                - fft_values (np.ndarray): The raw FFT values of the signal.
                - frequencies (np.ndarray | None): The frequency bins if sample_rate is provided; otherwise, None.
                - magnitude (np.ndarray): The magnitudes of the FFT values.
        """
        fourier = np.fft.fft(signal)
        magnitude = np.abs(fourier)[: len(fourier) // 2]

        if sample_rate is not None:
            frequencies = np.fft.fftfreq(len(signal), 1 / sample_rate)[: len(fourier) // 2]
            return fourier, frequencies, magnitude

        return fourier, None, magnitude

    @staticmethod
    def find_max_frequency(signal: np.ndarray, sample_rate: float) -> float:
        """Finds the maximum frequency component in a signal.

        Args:
            signal (np.ndarray): The input signal as a 1D numpy array.
            sample_rate (float): The sample rate of the signal.

        Returns:
            float: The maximum frequency present in the signal.
        """
        fourier, frequencies, _ = SignalAnalyzer.compute_fft_frequency_magnitude(signal, sample_rate)

        return np.max(frequencies)

    @staticmethod
    def plot_frequency_magnitude(name: str, signal: np.ndarray, sample_rate: float) -> None:
        """Plots the magnitude of the FFT frequencies in a signal.

        Args:
            name (str): The title of the plot and filename to save the image.
            signal (np.ndarray): The input signal as a 1D numpy array.
            sample_rate (float): The sample rate of the signal.

        Returns:
            None
        """
        fourier, frequencies, magnitude = SignalAnalyzer.compute_fft_frequency_magnitude(signal, sample_rate)

        fig, ax = plt.subplots(1)
        fig.suptitle(name)

        plt.yscale("log")
        plt.xscale("log")

        ax.plot(frequencies, magnitude, linewidth=0.75)

        ax.set_xlim([1.5e-8, np.max(frequencies)])

        plt.savefig(f"plots/{name}.pdf", format="pdf")
        plt.savefig(f"plots/{name}.png", format="png")
        plt.show()

    @staticmethod
    def remove_continuous_component(signal: np.ndarray) -> np.ndarray:
        """Removes the continuous component (DC offset) from a signal.

        Args:
            signal (np.ndarray): The input signal as a 1D numpy array.

        Returns:
            np.ndarray: The signal with the continuous component subtracted.

        Raises:
            ValueError: If there is no continuous component in the signal.
        """
        fourier, _, _ = SignalAnalyzer.compute_fft_frequency_magnitude(signal)
        continous_component_value = np.abs(fourier[0]) / len(fourier)

        if continous_component_value == 0:
            raise ValueError("There is no continous component")

        return np.subtract(signal, continous_component_value)

    @staticmethod
    def get_top_k_frequencies(signal: np.ndarray, sample_rate: float, k: int = 1) -> np.ndarray:
        """Finds the top K frequencies with the highest magnitude in a signal.

        Warnings:
            The signal should be normalized before calling this function to ensure accurate frequency magnitude comparison.

        Args:
            signal (np.ndarray): The input signal as a 1D numpy array.
            sample_rate (float): The sample rate of the signal.
            k (int, optional): The number of top frequencies to return. Default is 1.

        Returns:
            np.ndarray: An array of the top K frequencies in the signal.
        """
        fourier, frequencies, magnitude = SignalAnalyzer.compute_fft_frequency_magnitude(signal, sample_rate)

        sorted_magnitude_indices = np.argsort(magnitude)[-k:][::-1]
        return frequencies[sorted_magnitude_indices]

    @staticmethod
    def filter_signal(signal: np.ndarray, filter_amount: float = 0.95) -> np.ndarray:
        """Filters the given signal in the frequency domain by removing components
        below a certain magnitude threshold determined by the specified filter amount.

        Args:
            signal (np.ndarray): The input signal as a 1D numpy array.
            filter_amount (float, optional):
                The proportion of the signal's magnitude spectrum to retain.
                Should be between 0 and 1, with a default value of 0.95.

        Raises:
            ValueError: If filter_amount is not between 0 and 1.

        Returns
            np.ndarray:
                The filtered signal obtained by applying the inverse Fourier transform
                to the modified frequency domain representation.
        """
        if not (0 <= filter_amount <= 1):
            raise ValueError("Filter amount must be between 0 and 1")

        fourier = np.fft.fft(signal)
        magnitude = np.abs(fourier)

        threshold = np.percentile(magnitude, filter_amount * 100)
        indices_to_remove = np.where(magnitude <= threshold)[0]

        for index in indices_to_remove:
            fourier[index] = 0 + 0j

        return np.real(np.fft.ifft(fourier))


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
