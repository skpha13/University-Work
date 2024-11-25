import os

import matplotlib.pyplot as plt
import numpy as np
from utils.models import ARModel
from utils.plot import plot
from utils.sinewave import sinusoidal_signal

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)

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
ps = [7, 14, 30]
ms = [N // 4, N // 2, N]

# TODO: kfolds + mean and then output each on a graph
for m in ms:
    for p in ps:
        ar = ARModel()
        ar.fit(series, p, m)
        mse = ar.mse()
        print(mse)
