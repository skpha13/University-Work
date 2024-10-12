"""Exercise 1"""

import numpy as np

from utils.plot import plot
from utils.sinewave import cosinus_signal, sinusoidal_signal

t = 1
n = 1000
nts = np.linspace(0, t, n)

sin = sinusoidal_signal(n=n)
# shift cosinus by the inverse of pi/2 for sinus
cos = cosinus_signal(phi=-np.arcsin(np.sin(np.pi / 2)), n=n)

plot("Sin vs Cos", nts, sin, cos, xlim=None)
