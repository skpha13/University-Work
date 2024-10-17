import numpy as np


def fourier_transform(N: int):
    fourier_matrix = np.zeros((N, N), dtype=np.complex64)

    for i in range(N):
        for j in range(N):
            fourier_matrix[i][j] = np.exp(-2 * np.pi * 1j * j * i / N)

    return fourier_matrix


def display_matrix(matrix: np.ndarray):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(f"{matrix[i][j].real} + {matrix[i][j].imag}j", end=" ")

        print()
