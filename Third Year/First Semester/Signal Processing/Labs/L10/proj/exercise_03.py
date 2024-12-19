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
    p = 14
    m = 220

    fold_size = N // 4
    folds, y_true = kfold_split(series, fold_size)

    y_pred_base = []

    for fold in folds:
        ar = AR(p, m)
        ar.fit(fold)
        y_pred_base.append(ar.predict())

    y_pred_base = np.array(y_pred_base)

    mse = mean_squared_error(y_true, y_pred_base)
    print(mse)


def main_sparse():
    series = np.array([i for i in range(10)])

    p = 3
    m = 2
    model = ARSparse(p, m)
    model.fit(series)


if __name__ == "__main__":
    main_sparse()
