import numpy as np
import matplotlib.pyplot as plt
from numpy import ndarray

real_axis = np.arange(0, 0.03, 0.0005)

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

plt.show()

samples = np.linspace(0, 0.03, 200)
x_values_sampled = x(samples)
y_values_sampled = y(samples)
z_values_sampled = z(samples)

fig, axs = plt.subplots(3)
fig.suptitle("Sampled Signal Graphs")

axs[0].stem(samples, x_values_sampled)
axs[1].stem(samples, y_values_sampled)
axs[2].stem(samples, z_values_sampled)

plt.show()

def sinusoidal_signal(A: float, f: float, t: float, phi: float, n: int) -> ndarray:
    ts = np.linspace(0, t, n)
    return A * np.sin(2 * np.pi * f * n * ts + phi)

values_1600 = sinusoidal_signal(1, 400, 1, 0, 1600)
fig, ax = plt.subplots()
fig.suptitle("1600 samples")
ax.stem(np.linspace(0, 1, 1600), values_1600)
plt.show()

values_800 = sinusoidal_signal(1, 800, 3, 0, 800)
fig, ax = plt.subplots()
fig.suptitle("800 samples 3 seconds")
ax.stem(np.linspace(0, 3, 800), values_800)
plt.show()

sawtooth = np.floor(sinusoidal_signal(1, 240, 5, 0, 200))
fig, ax = plt.subplots()
fig.suptitle("Sawtooth")
ax.plot(np.linspace(0, 5, 200), sawtooth)
plt.show()

square = np.floor(sinusoidal_signal(1, 300, 5, 0, 200))
fig, ax = plt.subplots()
fig.suptitle("Square")
ax.plot(np.linspace(0, 5, 200), square)
plt.show()

random_signal = np.random.rand(128, 128)
plt.imshow(random_signal)

random_signal_generated = np.zeros((128, 128))
plt.imshow(random_signal_generated)
