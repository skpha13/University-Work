"""Exercise 5"""

import numpy as np

from utils.audio import Audio
from utils.sinewave import sinusoidal_signal

t = 1
n = 1000
sin_low = sinusoidal_signal(1, 200, t, 0, n)
sin_high = sinusoidal_signal(1, 1000, t, 0, n)
low_high_concat = np.concatenate((sin_low, sin_high))

Audio.write("low_vs_high.wav", data=low_high_concat)
Audio.play("low_vs_high.wav", loop=True, duration=1000)

"""Observations:

    The generated sound is a transition between the two signals, in other terms the first one is played,
and right after begins the second one (they are played in sequence).
"""
