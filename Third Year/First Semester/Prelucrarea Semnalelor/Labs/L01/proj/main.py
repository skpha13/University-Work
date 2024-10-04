import numpy as np
import matplotlib.pyplot as plt

from proj.sinewave import sinusoidal_signal
from proj.plot import plot, stem

"""Exercise 1"""

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

"""Exercise 2"""

# (a)
t = 1
n = 1600
stem("1600 samples", np.linspace(0, t, n), sinusoidal_signal(1, 400, t, 0, n))

# (b)
t = 3
n = 800
stem("800 samples 3 seconds", np.linspace(0, t, n), sinusoidal_signal(1, 800, t, 0, n))

# (c)
t = 5
n = 200
plot("Sawtooth", np.linspace(0, t, n), np.floor(sinusoidal_signal(1, 240, t, 0, n)))

# (d)
t = 5
n = 200
plot("Square", np.linspace(0, t, n), np.floor(sinusoidal_signal(1, 300, 5, 0, 200)))

# (e)
random_signal = np.random.rand(128, 128)
plt.imshow(random_signal)

# (f)
random_signal_generated = np.zeros((128, 128))
plt.imshow(random_signal_generated)
