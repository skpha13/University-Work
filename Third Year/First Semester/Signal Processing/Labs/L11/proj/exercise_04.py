import matplotlib.pyplot as plt
import numpy as np
from utils.signal import dehankelize_matrix, hankelize_matrix, hankelize_series, predefined_series


def main():
    N = 1000
    series = predefined_series(N)

    L = 200
    X = hankelize_series(series, L)

    U, S, V = np.linalg.svd(X, full_matrices=False)

    hankelized_matrix = np.zeros(V.shape)
    for i in range(len(S)):
        Xi = S[i] * np.outer(U[i].T, V[i])

        hankelized_xi = hankelize_matrix(Xi)
        hankelized_matrix += hankelized_xi

    dehankelized_matrix = dehankelize_matrix(hankelized_matrix)

    print(dehankelized_matrix.shape)

    plt.plot(np.linspace(0, 1, dehankelized_matrix.shape[0]), series)
    plt.plot(np.linspace(0, 1, dehankelized_matrix.shape[0]), dehankelized_matrix)
    plt.show()


def test_hankel_matrix():
    x = np.zeros((5, 7))
    value = 1

    for i in range(x.shape[0]):
        for j in range(x.shape[1]):
            x[i][j] = value
            value += 1

    x = np.array(x)

    hankel = hankelize_matrix(x)
    print(hankel)

    dehankel = dehankelize_matrix(hankel)
    print(dehankel)


if __name__ == "__main__":
    main()
