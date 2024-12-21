import numpy as np
from matplotlib import pyplot as plt

from utils.sinewave import sinusoidal_signal


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


def kfold_split(series: np.ndarray, k: int) -> tuple[np.ndarray, np.ndarray]:
    """Splits a 1D series into k folds.

    Args:
        series (numpy array): 1D array to be split.
        k (int): Number of folds.

    Returns:
        list of numpy arrays: List of k folds.
    """

    folds = []
    y_true = []
    step = 1

    for i in range(0, len(series) - k + 1, step):
        if i + k >= len(series):
            break

        folds.append(series[i : i + k])
        y_true.append(series[i + k])

    return np.array(folds), np.array(y_true)


def hankelize_series(series: np.ndarray, L: int) -> np.ndarray:
    """Generates a Hankel-like matrix from a given time series, where sliding windows
    of length L are represented as columns.

    Args:
        series (np.ndarray): The input time series as a 1D NumPy array.
        L (int): The length of each sliding window.

    Returns:
        np.ndarray: A 2D NumPy array where each column is a sliding window of length L
        extracted from the input series.
    """

    hankel_matrix = []

    for i in range(0, len(series) - L + 1):
        hankel_matrix.append(series[i : i + L])

    return np.array(hankel_matrix).T


def hankelize_matrix(matrix: np.ndarray) -> np.ndarray:
    """Creates a Hankelized version of the given matrix by modifying its anti-diagonal elements.

    This function iterates over the matrix, calculating the mean of the anti-diagonal elements
    for each diagonal and replacing those elements with the calculated mean. A Hankelized matrix
    has constant values along each anti-diagonal.

    Args:
        matrix (np.ndarray): The input 2D square numpy array to be Hankelized.

    Returns:
        np.ndarray: A new matrix where each anti-diagonal has been replaced with the mean of
                    the original anti-diagonal values.
    """
    rows, cols = matrix.shape
    hankelized_matrix = np.copy(matrix)

    def fill_with_mean(hankelized_matrix: np.ndarray, matrix: np.ndarray, indices: np.ndarray) -> np.ndarray:
        row_indices = indices[:, 0]
        col_indices = indices[:, 1]

        anti_diagonal_elements = matrix[row_indices, col_indices]
        mean = np.mean(anti_diagonal_elements)
        hankelized_matrix[row_indices, col_indices] = mean

        return hankelized_matrix

    # upper triangle
    for diag in range(1, rows):
        indices = np.array([[diag - i, i] for i in range(diag + 1)])
        hankelized_matrix = fill_with_mean(hankelized_matrix, matrix, indices)

    # everything in between
    diag = rows - 1
    for column_offset in range(1, cols - rows + 1):
        indices = np.array([[diag - i, i + column_offset] for i in range(diag + 1)])
        hankelized_matrix = fill_with_mean(hankelized_matrix, matrix, indices)

    # lower triangle
    diag = rows - 1
    for column_offset in range(cols - rows + 1, cols - 1):
        indices = np.array([[diag - i, i + column_offset] for i in range(diag)])
        hankelized_matrix = fill_with_mean(hankelized_matrix, matrix, indices)
        diag -= 1

    return hankelized_matrix


def dehankelize_matrix(matrix: np.ndarray) -> np.ndarray:
    dehankelized_matrix = matrix[:, 0]
    dehankelized_matrix = np.concatenate((dehankelized_matrix, matrix[-1, 1:]))

    return dehankelized_matrix


def predefined_series(N: int = 1000) -> np.ndarray:
    ts = np.linspace(0, 1, N)
    trend_function = lambda x: x**2
    trend = np.array([trend_function(x) for x in ts])
    season = sinusoidal_signal(0.1, 5, 1, 0, N) + sinusoidal_signal(0.2, 3, 1, 0, N)
    noise = np.random.normal(0, 0.01, N)
    series = trend + season + noise

    return series
