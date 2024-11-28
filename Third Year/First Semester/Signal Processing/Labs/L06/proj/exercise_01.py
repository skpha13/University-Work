import os
import random

import matplotlib.pyplot as plt
import numpy as np

seed = 0
np.random.seed(seed)
random.seed(seed)

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

x = np.random.rand(100)

x2 = np.convolve(x, x)
x4 = np.convolve(x2, x2)
x8 = np.convolve(x4, x4)

name = "Repeated Convolution"
fig, ax = plt.subplots(1)
fig.suptitle(name)

ax.plot(np.linspace(1, 0, len(x)), x)
ax.plot(np.linspace(1, 0, len(x2)), x2)
ax.plot(np.linspace(1, 0, len(x4)), x4)
ax.plot(np.linspace(1, 0, len(x8)), x8)

plt.savefig(f"plots/{name}.pdf", format="pdf")
plt.savefig(f"plots/{name}.png", format="png")

plt.show()
