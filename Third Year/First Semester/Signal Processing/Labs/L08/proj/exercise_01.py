import matplotlib.pyplot as plt
import numpy as np
from utils.plot import plot
from utils.sinewave import sinusoidal_signal

# a)

N = 1000
ts = np.linspace(0, 1, N)
trend_function = lambda x: x**2
trend = np.array([trend_function(x) for x in ts])
season = sinusoidal_signal(0.1, 5, 1, 0, N) + sinusoidal_signal(0.2, 3, 1, 0, N)
noise = np.random.normal(0, 0.01, N)
series = trend + season + noise

plot("Trend, Season, Variety", ts, series, trend, season, noise)

# b)
padded_series = np.pad(series, (N, N), "constant")
autocorrelation = []

# TODO: refactor this in utils.py and add all modes
# 1 to start from the first intersection (last element and first element)
for k in range(1, 2 * N):
    autocorrelation.append(np.dot(series, padded_series[k : k + N]))

autocorrelation_np = np.correlate(series, series, mode="full")
fig, axs = plt.subplots(2)
plot_name = "Autocorrelation"
fig.suptitle(plot_name)
axs[0].plot(np.arange(0, len(autocorrelation)), autocorrelation)
axs[1].plot(np.arange(0, len(autocorrelation_np)), autocorrelation_np)
plt.show()

# c)
