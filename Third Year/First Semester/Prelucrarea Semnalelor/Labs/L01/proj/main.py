import matplotlib.pyplot as plt
import numpy as np

from plot import plot, stem
from sinewave import sinusoidal_signal

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
t = 1
n = 1_000_000
signal = sinusoidal_signal(1, 240, t, 0, n)
sawtooth_signal = np.abs(signal)
sawtooth_signal = np.mod(sawtooth_signal, 0.1)
plot("Sawtooth", np.linspace(0, t, n), sawtooth_signal, xlim=[0, 614e-6])

# (d)
t = 1000
n = 10_000
plot("Square", np.linspace(0, t, n), np.sign(sinusoidal_signal(1, 300, t, 0, n)))

# (e)
cmap = "binary"
random_signal = np.random.rand(128, 128)
plt.imshow(random_signal, cmap=cmap)
plt.savefig(fname=f"./plots/random_image.pdf", format="pdf")
plt.show()
plt.close()

# (f)
generated_signal = np.full((128, 128), 128)
plt.imshow(generated_signal, cmap=cmap, vmin=0, vmax=255)
plt.savefig(fname=f"./plots/zeroed_image.pdf", format="pdf")
plt.show()

"""Exercise 3"""

# (a)

"""
Depends on the value of t (time), a general formula would be t / 2000
For 1s:
    1 / 2000 = 0.0005s (0.5ms)
"""

# (b)

"""
Analogue to (a), depends on value of t (time)
General formula: (4 * f * t) / 8 bytes
For 1s:
    (4 * 2000 * 1) / 8
    8000 / 8
    1000 bytes
"""
