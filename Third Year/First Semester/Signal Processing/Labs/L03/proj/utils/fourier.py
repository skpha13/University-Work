import numpy as np


def fourier_transform(N: int) -> np.ndarray:
    fourier_matrix = np.zeros((N, N), dtype=np.complex64)

    for i in range(N):
        for j in range(N):
            fourier_matrix[i][j] = np.exp(-2 * np.pi * 1j * j * i / N)

    return fourier_matrix


def display_matrix(matrix: np.ndarray) -> None:
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(f"{matrix[i][j].real} + {matrix[i][j].imag}j", end=" ")

        print()


def winding_frequency_on_unit_circle(x: np.ndarray, omegas: list[float]) -> np.ndarray:
    z = []

    for omega in omegas:
        zw = [x[i] * np.exp(-2 * np.pi * 1j * omega * i / len(x)) for i in range(len(x))]
        z.append(zw)

    return np.array(z)
