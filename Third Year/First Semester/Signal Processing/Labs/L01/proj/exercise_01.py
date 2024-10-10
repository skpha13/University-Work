"""Exercise 1"""

import matplotlib.pyplot as plt
import numpy as np

# (a)
real_axis = np.arange(0, 0.03, 0.0005)

# (b)
x = lambda a: np.cos(520 * np.pi * a + np.pi / 3)
y = lambda a: np.cos(280 * np.pi * a - np.pi / 3)
z = lambda a: np.sin(120 * np.pi * a + np.pi / 3)

fig, axs = plt.subplots(3)
fig.suptitle("Base Signal Graphs")

x_values = x(real_axis)
y_values = y(real_axis)
z_values = z(real_axis)

axs[0].plot(real_axis, x_values)
axs[1].plot(real_axis, y_values)
axs[2].plot(real_axis, z_values)
plt.savefig(fname="./plots/xyz_signals.pdf", format="pdf")
plt.show()

# (c)
samples = np.linspace(0, 0.03, 200)
x_values_sampled = x(samples)
y_values_sampled = y(samples)
z_values_sampled = z(samples)

fig, axs = plt.subplots(3)
fig.suptitle("Sampled Signal Graphs")

axs[0].stem(samples, x_values_sampled)
axs[1].stem(samples, y_values_sampled)
axs[2].stem(samples, z_values_sampled)

plt.savefig(fname="./plots/xyz_signals_sampled.pdf", format="pdf")
plt.show()
