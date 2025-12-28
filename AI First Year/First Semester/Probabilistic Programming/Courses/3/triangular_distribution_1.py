import pymc as pm
import numpy as np
from matplotlib import pyplot as plt

def triangular_logp(value, a, b, c):
    if a <= value < c:
        return np.log((2. * (value - a)) / ((b - a) * (c - a)))
    if value == c:
        return np.log(2. / (b - a))
    if c < value <= b:
        return np.log((2. * (b - value)) / ((b - a) * (b - c)))
    return -np.inf

def triangular_random(a, b, c, rng=None, size=None):
    return np.random.triangular(a, c, b, size)                       

with pm.Model() as model:                                  
    Z = pm.CustomDist(
        'Z',
        -3, 8, 0,
        logp=triangular_logp,
        random=triangular_random,
    )


Z_samples = pm.draw(Z, draws=40000)

plt.hist(Z_samples, bins = 40)
plt.show()



