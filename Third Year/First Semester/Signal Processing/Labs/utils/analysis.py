import numpy as np
from sklearn.decomposition import PCA


class SingleSpectrumAnalysis:
    """A class for performing Single Spectrum Analysis (SSA) on a time series.

    Attributes:
        L (int): The window length used to create the Hankel matrix.
    """

    COMPONENTS_PERCENT: float = 0.98

    def __init__(self, L: int):
        self.L = L
        self.PCA = PCA(n_components=SingleSpectrumAnalysis.COMPONENTS_PERCENT)

    @staticmethod
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

    @staticmethod
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

    @staticmethod
    def dehankelize_matrix(matrix: np.ndarray) -> np.ndarray:
        """Converts a Hankel matrix back into a single vector.

        Args:
            matrix (np.ndarray): The Hankel matrix to be de-Hankelized.

        Returns:
            np.ndarray: The reconstructed time series vector.
        """

        dehankelized_matrix = matrix[:, 0]
        dehankelized_matrix = np.concatenate((dehankelized_matrix, matrix[-1, 1:]))

        return dehankelized_matrix

    def analyze(self, series: np.ndarray) -> np.ndarray:
        """Performs SSA analysis on the input time series.

        Args:
            series (np.ndarray): The input time series to be analyzed. Must be a one-dimensional array.

        Returns:
            np.ndarray: The reconstructed time series after SSA analysis.
        """

        X = SingleSpectrumAnalysis.hankelize_series(series, self.L)

        X_reduced = self.PCA.fit_transform(X)
        X_reconstructed = self.PCA.inverse_transform(X_reduced)

        U, S, V = np.linalg.svd(X_reconstructed, full_matrices=False)

        hankelized_matrix = np.zeros(V.shape)
        for i in range(len(S)):
            Xi = S[i] * np.outer(U.T[i], V[i])

            hankelized_xi = SingleSpectrumAnalysis.hankelize_matrix(Xi)
            hankelized_matrix += hankelized_xi

        dehankelized_matrix = SingleSpectrumAnalysis.dehankelize_matrix(hankelized_matrix)

        return dehankelized_matrix
