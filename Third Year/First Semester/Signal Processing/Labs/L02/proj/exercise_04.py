"""Exericise 4"""

import numpy as np

from utils.plot import plot
from utils.sinewave import sinusoidal_signal

t = 1
n = 1_000_000
nts = np.linspace(0, t, n)

sin = sinusoidal_signal(1, 240, t, 0, n)
sawtooth = np.arcsin(np.abs(sin))
sawtooth = np.mod(sawtooth, 0.1)
sin_sawtooth_added = np.add(sin, sawtooth)

plot("Added Samplings", nts, sin, sawtooth, sin_sawtooth_added, xlim=[0, 0.005])
