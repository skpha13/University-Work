import os

import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import root_mean_squared_error
from utils.models import EMA
from utils.signal import predefined_series

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)

# 1)

N = 1000
ts = np.linspace(0, 1, N)
series = predefined_series(N)

# 2)
alphas = []
errors = []

for alpha in np.linspace(0, 1, 1000):
    clf = EMA(alpha)
    ema = clf.fit(series)[: len(series) - 1]
    offset_series = series[1:]

    alphas.append(alpha)
    errors.append(root_mean_squared_error(offset_series, ema))

min_error_index = np.argmin(errors)
best_alpha = alphas[min_error_index]

plot_name = "Error"
fig, ax = plt.subplots()
fig.suptitle(plot_name)
ax.plot(alphas, errors)
ax.plot(best_alpha, errors[min_error_index], "ro")
plt.yscale("log")

plt.savefig(f"plots/{plot_name}.png", format="png")
plt.show()

preview_index = N // 4

print(f"Most Optimum Alpha: {best_alpha:.4f}")
clf = EMA(best_alpha)
ema = clf.fit(series)[: len(series) - 1]
offset_series = series[1:]

plot_name = "Exponential Moving Average (EMA)"
fig, ax = plt.subplots()
fig.suptitle(plot_name)
ax.plot(ts[:preview_index], offset_series[:preview_index])
ax.plot(ts[:preview_index], ema[:preview_index])

plt.savefig(f"plots/{plot_name}.png", format="png")
plt.show()
