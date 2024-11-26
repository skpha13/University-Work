import os

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import Normalize
from sklearn.metrics import mean_squared_error
from utils.models import ARModel
from utils.plot import plot
from utils.signal import kfold_split
from utils.sinewave import sinusoidal_signal

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)

# a)

N = 1000
ts = np.linspace(0, 1, N)
trend_function = lambda x: x**2
trend = np.array([trend_function(x) for x in ts])
season = sinusoidal_signal(0.1, 5, 1, 0, N) + sinusoidal_signal(0.2, 3, 1, 0, N)
noise = np.random.normal(0, 0.01, N)
series = trend + season + noise

plot("Trend, Season, Noise", ts, series, trend, season, noise, titles=["Original", "Trend", "Season", "Noise"])

# b)
padded_series = np.pad(series, N, "constant")
autocorrelation = []

# 1 to start from the first intersection (last element and first element)
for k in range(1, 2 * N):
    autocorrelation.append(np.dot(series, padded_series[k : k + N]))

autocorrelation = autocorrelation[:N]

autocorrelation_np = np.correlate(series, series, mode="full")[:N]
fig, axs = plt.subplots(2)
plot_name = "Autocorrelation"
fig.suptitle(plot_name)

axs[0].plot(np.arange(-len(autocorrelation), 0), autocorrelation)
axs[0].set_title("My correlation")
plt.xlabel("Lag")
plt.ylabel("Correlation")

axs[1].plot(np.arange(-len(autocorrelation_np), 0), autocorrelation_np)
axs[1].set_title("Numpy correlation")

plt.tight_layout()
plt.savefig(f"plots/{plot_name}.pdf", format="pdf")
plt.show()

# c)

ar = ARModel()
p = 7
m = N // 2
ar.fit(series, p, m)
y_value = ar.predict()

answer_c = f"""The predicted value for p={p} and m={m} is: {y_value}"""
print(answer_c)

# d)

fold_size = N // 4
folds, y_true = kfold_split(series, N // 4)
ps = [7, 14, 30]
ms = [fold_size // 4, fold_size // 2, fold_size - 30]
errors = []

for m in ms:
    for p in ps:
        y_pred = []

        for fold in folds:
            ar = ARModel()
            ar.fit(fold, p, m)
            y_pred.append(ar.predict())

        errors.append(mean_squared_error(y_true, y_pred))

error_matrix = np.zeros((len(ms), len(ps)))
for m_index, m in enumerate(ms):
    for p_index, p in enumerate(ps):
        error_matrix[m_index, p_index] = errors[len(ms) * m_index + p_index]

fig, ax = plt.subplots()
im = ax.imshow(error_matrix, cmap="inferno")
cbar = fig.colorbar(im, ax=ax)
cbar.set_label("Mean Squared Error")

ax.set_xticks(np.arange(len(ps)), labels=ps)
ax.set_yticks(np.arange(len(ms)), labels=ms)

# normalize the colormap for dynamic text color
norm = Normalize(vmin=np.min(error_matrix), vmax=np.max(error_matrix))

for i in range(len(ms)):
    for j in range(len(ps)):
        value = error_matrix[i, j]

        # breaking threshold for color
        color = "white" if norm(value) < 0.5 else "black"
        text = ax.text(j, i, f"{value:.06f}", ha="center", va="center", color=color)

ax.set_title("Mean Squared Error")

fig.tight_layout()
plt.savefig("plots/Mean Squared Error.pdf", format="pdf")
plt.show()

min_indices = np.unravel_index(np.argmin(error_matrix), error_matrix.shape)
best_m = min_indices[0]
best_ps = min_indices[1]
answer_d = f"""The best hyperparameters from the heatmap are: m={ms[best_m]}, p={ps[best_ps]}"""
print(answer_d)
