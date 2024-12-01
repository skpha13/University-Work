import os

import matplotlib.pyplot as plt
import numpy as np
from utils.models import MA
from utils.signal import predefined_series

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)
np.random.seed(0)

# 1)

N = 1000
series = predefined_series(N)

# 3)

ma = MA(1)
m = 7
predictions = []
for i in range(len(series) - m):
    ma.fit(series[i : i + m])
    predictions.append(ma.predict())

preview_index = N // 4
plot_name = "Moving Average Model (MA)"

fig, ax = plt.subplots()
fig.suptitle(plot_name)
xs = np.linspace(0, 1, preview_index)

ax.plot(xs, series[:preview_index])
# predictions only start after m point in time
ax.plot(xs[m:], predictions[: preview_index - m])

plt.savefig(f"plots/{plot_name}.png", format="png")
plt.show()
