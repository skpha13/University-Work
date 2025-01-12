import numpy as np
from utils.analysis import SingleSpectrumAnalysis
from utils.signal import predefined_series

seed = 0
np.random.seed(seed)


def main():
    N = 1000
    series = predefined_series(N)

    L = 200
    X = SingleSpectrumAnalysis.hankelize_series(series, L)

    xxt = X @ X.T
    xtx = X.T @ X

    x_singularvalues = np.linalg.svdvals(X)
    xxt_eigenvalues = np.sqrt(np.sort(np.linalg.eigvals(xxt)))[::-1]
    xtx_eigenvalues = np.sqrt(np.sort(np.linalg.eigvals(xtx)))[::-1][:200]

    print(f"Error between SVD and X @ XT: {np.linalg.norm(x_singularvalues - xxt_eigenvalues):.15f}")
    print(f"Error between SVD and XT @ X: {np.linalg.norm(x_singularvalues - xtx_eigenvalues):.15f}")


if __name__ == "__main__":
    main()
