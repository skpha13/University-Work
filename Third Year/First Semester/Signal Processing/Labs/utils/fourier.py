import numpy as np


def fourier_transform_matrix(N: int) -> np.ndarray:
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


def fourier_transform(x: np.ndarray, number_of_components: int = None) -> np.ndarray:
    """Computes the discrete Fourier transform (DFT) of a given signal

    Args:
        x (np.ndarray): The input array representing the signal in the time domain.

        number_of_components (int, optional): The number of Fourier components to compute.
            If None, the length of the input array `x` is used as the number of components.

    Returns:
        np.ndarray: The Fourier-transformed array, representing the signal in the frequency domain.
    """

    n = len(x) if number_of_components is None else number_of_components
    X = np.zeros(n, dtype=np.complex128)

    for m in range(n):
        component_sum = 0

        for k in range(n):
            component_sum += x[k] * np.exp(-2 * np.pi * 1j * k * m / n)

        X[m] = component_sum

    return X


def fourier_transform_using_winding_frequency(x: np.ndarray, omegas: list[float]) -> dict[float, np.complex128]:
    """Computes the Fourier transform at specified winding frequencies.

    Args:
        x (np.ndarray): The input signal array representing the signal in the time domain.
        omegas (list[float]): A list of winding frequencies where the Fourier transform is to be evaluated.

    Returns:
        dict[float, np.complex128]: A dictionary where each key is a winding frequency from `omegas`,
        and the corresponding value is the Fourier transform result (complex number) at that frequency.
    """

    X: dict[float, np.complex128] = {}

    winding_frequencies = winding_frequency_on_unit_circle(x, omegas)

    for index, vector in enumerate(winding_frequencies):
        X[omegas[index]] = np.sum(vector)

    return X


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
