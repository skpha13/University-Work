import os

import numpy as np
from matplotlib import pyplot as plt
from skimage.metrics import mean_squared_error
from utils.models import AR, ARSparse
from utils.signal import kfold_split, predefined_series

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)


def main():
    N = 1000
    series = predefined_series(N)

    p = 16
    m = 128

    fold_size = N - 32
    folds, y_true = kfold_split(series, fold_size)

    y_pred_base = []
    y_pred_sparse = []

    for fold in folds:
        ar = AR(p, m)
        ar.fit(fold)
        y_pred_base.append(ar.predict())

        ar_sparse = ARSparse(256, m, p)
        ar_sparse.fit(series)
        y_pred_sparse.append(ar_sparse.predict())

    y_pred_base = np.array(y_pred_base)
    y_pred_sparse = np.array(y_pred_sparse)

    mse_base = mean_squared_error(y_true, y_pred_base)
    mse_sparse = mean_squared_error(y_true, y_pred_sparse)

    print(f"AR error: {mse_base}\nARSparse error: {mse_sparse}")


def main_predict():
    N = 1000
    series = predefined_series(N)

    window_size = 200
    sliding_windows = np.lib.stride_tricks.sliding_window_view(series, window_shape=window_size)
    y_pred_sparse = []

    for window in sliding_windows:
        ar_sparse = ARSparse(64, 64, 16)
        ar_sparse.fit(window)
        y_pred_sparse.append(ar_sparse.predict())

    y_pred_sparse = np.array(y_pred_sparse)

    preview_offset = 600
    preview_index = 700
    plot_name = "ARSparse Predictions"

    fig, ax = plt.subplots()
    fig.suptitle(plot_name)
    xs = np.linspace(0, 1, preview_index)

    ax.plot(xs[preview_offset:], series[preview_offset:preview_index])
    # predictions only start after window-size point in time
    ax.plot(
        xs[preview_offset:],
        y_pred_sparse[preview_offset - window_size : preview_index - window_size],
        color="red",
    )

    plt.savefig(f"plots/{plot_name}.svg", format="svg")
    plt.show()


def main_integer_series():
    series = np.array([i for i in range(10)])

    p = 3
    m = 2

    model = ARSparse(p, m, 2)
    model.fit(series)
    print(model.predict())


if __name__ == "__main__":
    main()
