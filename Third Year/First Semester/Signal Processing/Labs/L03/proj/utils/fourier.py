import numpy as np


def fourier_transform(N: int) -> np.ndarray:
    """Generate the Fourier Transform matrix of size N x N.

    This function constructs a complex-valued Fourier Transform matrix,
    where each element is calculated using the formula for the Discrete Fourier Transform (DFT).

    Args:
        N (int): The size of the Fourier Transform matrix.

    Returns:
        np.ndarray: A complex-valued (N x N) NumPy array representing the Fourier Transform matrix.
    """

    fourier_matrix = np.zeros((N, N), dtype=np.complex64)

    for i in range(N):
        for j in range(N):
            fourier_matrix[i][j] = np.exp(-2 * np.pi * 1j * j * i / N)

    return fourier_matrix


def display_matrix(matrix: np.ndarray) -> None:
    """Display the contents of a complex matrix.

    This function prints each element of the input matrix in the form of
    'real_part + imaginary_part j'.

    Args:
        matrix (np.ndarray): A NumPy array of complex numbers to be displayed.

    Returns:
        None: This function does not return a value; it prints the matrix to the console.
    """
    if not np.iscomplexobj(matrix):
        raise ValueError("Input matrix must contain complex numbers")

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(f"{matrix[i][j].real} + {matrix[i][j].imag}j", end=" ")

        print()


def winding_frequency_on_unit_circle(x: np.ndarray, omegas: list[float]) -> np.ndarray:
    """Calculate the winding frequency of a signal on the unit circle.

    This function computes the winding frequency for a given signal over a list of angular frequencies
    using the formula for complex exponentials.

    Args:
        x (np.ndarray): A NumPy array representing the signal values.
        omegas (list[float]): A list of angular frequencies at which to evaluate the winding frequency.

    Returns:
        np.ndarray: A 2D NumPy array where each row corresponds to the winding frequency
                    of the signal at a specific angular frequency.
    """
    z = []

    for omega in omegas:
        zw = [x[i] * np.exp(-2 * np.pi * 1j * omega * i / len(x)) for i in range(len(x))]
        z.append(zw)

    return np.array(z)
