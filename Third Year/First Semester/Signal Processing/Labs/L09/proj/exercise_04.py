import os
import pickle
import warnings

import numpy as np
from matplotlib import pyplot as plt
from statsmodels.tools.sm_exceptions import ConvergenceWarning
from statsmodels.tsa.arima.model import ARIMA
from utils.models import ARMA
from utils.signal import predefined_series

# fmt: off
warnings.filterwarnings("ignore", category=ConvergenceWarning)
warnings.filterwarnings("ignore", message="Non-invertible starting MA parameters found. Using zeros as starting parameters.")
warnings.filterwarnings("ignore", message="Non-stationary starting autoregressive parameters found. Using zeros as starting parameters.")
# fmt: on

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)

# 1)

N = 1000
series = predefined_series(N)

# 4)

window_size = 30
sliding_windows = np.lib.stride_tricks.sliding_window_view(series, window_shape=window_size)

p = 1
q = 7
predictions = []
predictions_arima = []

file_path = "data/predictions_arima.pkl"
are_predictions_arima_loaded = False

if os.path.exists(file_path):
    with open(file_path, "rb") as file:
        predictions_arima = pickle.load(file)
        are_predictions_arima_loaded = True

for window in sliding_windows:
    arma = ARMA(p, q)
    arma.fit(window)
    predictions.append(arma.predict())

    if not are_predictions_arima_loaded:
        arima = ARIMA(window, order=(p, 1, q))
        arima_fit = arima.fit()
        next_prediction = arima_fit.forecast(steps=1)
        predictions_arima.append(next_prediction[0])

if not are_predictions_arima_loaded:
    with open("data/predictions_arima.pkl", "wb") as file:
        pickle.dump(predictions_arima, file)

preview_index = N // 8
plot_name = "Auto Regressive Moving Average Model (ARMA)"

fig, ax = plt.subplots()
fig.suptitle(plot_name)
xs = np.linspace(0, 1, preview_index)

ax.plot(xs, series[:preview_index])
# predictions only start after window-size point in time
ax.plot(xs[window_size:], predictions[: preview_index - window_size], color="red")
ax.plot(xs[window_size:], predictions_arima[: preview_index - window_size], color="black")

plt.legend(["Raw Series", "Custom ARMA", "ARIMA"])

plt.savefig(f"plots/{plot_name}.png", format="png")
plt.show()
