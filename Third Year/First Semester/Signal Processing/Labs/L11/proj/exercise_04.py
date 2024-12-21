import os

import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import root_mean_squared_error
from utils.signal import dehankelize_matrix, hankelize_matrix, hankelize_series, predefined_series

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)


def main():
    N = 1000
    series = predefined_series(N)

    L = 200
    X = hankelize_series(series, L)

    U, S, V = np.linalg.svd(X, full_matrices=False)

    hankelized_matrix = np.zeros(V.shape)
    for i in range(len(S)):
        Xi = S[i] * np.outer(U.T[i], V[i])

        hankelized_xi = hankelize_matrix(Xi)
        hankelized_matrix += hankelized_xi

    dehankelized_matrix = dehankelize_matrix(hankelized_matrix)

    error = root_mean_squared_error(series, dehankelized_matrix)

    print(f"Difference between Series and SSA: {error}")

    plot_name = "Singular Spectrum Analysis"
    plt.title(plot_name)

    preview_offset = 600
    preview_index = 700
    xs = np.linspace(0, 1, preview_index)

    plt.plot(xs[preview_offset:], series[preview_offset:preview_index])
    plt.plot(xs[preview_offset:], dehankelized_matrix[preview_offset:preview_index], color="red")

    plt.legend(["Raw Series", "SSA"])

    plt.savefig(f"plots/{plot_name}.svg", format="svg")
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
