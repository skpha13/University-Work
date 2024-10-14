"""Exercise 3"""

import numpy as np

from utils.audio import Audio
from utils.sinewave import sinusoidal_signal

fs = 44100

# (a)
t = 1
n = 1600
sin_1600 = sinusoidal_signal(1, 400, t, 0, n)

# (b)
t = 3
n = 800
sin_800 = sinusoidal_signal(1, 800, t, 0, n)

# (c)
t = 1
n = 1_000_000
signal = sinusoidal_signal(1, 240, t, 0, n)
sawtooth_signal = np.arcsin(np.abs(signal))
sawtooth_signal = np.mod(sawtooth_signal, 0.1)

# (d)
t = 1000
n = 10_000
square = np.sign(sinusoidal_signal(1, 300, t, 0, n))

Audio.write("sin_1600.wav", sin_1600)
Audio.play("sin_1600.wav", loop=True, duration=1000)

Audio.write("sin_800.wav", sin_800)
Audio.play("sin_800.wav", loop=True, duration=1000)

Audio.write("sawtooth.wav", sawtooth_signal)
Audio.play("sawtooth.wav", loop=True, duration=1000)

Audio.write("square.wav", square)
Audio.play("square.wav", loop=True, duration=1000)
