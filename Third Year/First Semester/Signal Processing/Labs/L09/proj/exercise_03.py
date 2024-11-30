import os

import matplotlib.pyplot as plt
import numpy as np
from utils.models import MA
from utils.sinewave import sinusoidal_signal

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)

# 1)

N = 1000
ts = np.linspace(0, 1, N)
trend_function = lambda x: x**2
trend = np.array([trend_function(x) for x in ts])
season = sinusoidal_signal(0.1, 5, 1, 0, N) + sinusoidal_signal(0.2, 3, 1, 0, N)
noise = np.random.normal(0, 0.01, N)
series = trend + season + noise

# lens = 100
# series = np.array([i for i in range(lens)])

ma = MA(1)
m = 3
predictions = []
for i in range(len(series) - m):
    ma.fit(series[i : i + m])
    predictions.append(ma.predict())

fig, ax = plt.subplots()
ax.plot(np.linspace(0, 1, N // 4), series[: N // 4])
ax.plot(np.linspace(0, 1, N // 4), predictions[: N // 4])

plt.show()

# print(predictions)
