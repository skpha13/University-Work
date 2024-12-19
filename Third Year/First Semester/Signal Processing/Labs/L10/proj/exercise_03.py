import os

import numpy as np
from skimage.metrics import mean_squared_error
from utils.models import AR, ARSparse
from utils.signal import kfold_split, predefined_series

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)


def main():
    N = 1000
    series = predefined_series(N)

    # values taken from L08 after grid search for p and m
    p = 16
    m = 64

    fold_size = N // 2
    folds, y_true = kfold_split(series, fold_size)

    y_pred_base = []
    y_pred_sparse = []

    for fold in folds:
        ar = AR(p, m)
        ar.fit(fold)
        y_pred_base.append(ar.predict())

        ar_sparse = ARSparse(64, 64, 16)
        ar_sparse.fit(series)
        y_pred_sparse.append(ar_sparse.predict())

    y_pred_base = np.array(y_pred_base)
    y_pred_sparse = np.array(y_pred_sparse)

    mse_base = mean_squared_error(y_true, y_pred_base)
    mse_sparse = mean_squared_error(y_true, y_pred_sparse)

    print(f"AR error: {mse_base}\nARSparse error: {mse_sparse}")


def main_sparse():
    series = np.array([i for i in range(10)])

    p = 3
    m = 2

    model = ARSparse(p, m, 2)
    model.fit(series)
    print(model.predict())


if __name__ == "__main__":
    main()
