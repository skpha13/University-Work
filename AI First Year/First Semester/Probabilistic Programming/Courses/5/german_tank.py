import numpy as np
import pymc as pm
from matplotlib import pyplot as plt


true_N = 500
D = np.random.randint(1, true_N + 1, size = 10)

print(D)

with pm.Model() as german_tank_model:
    N = pm.DiscreteUniform("N", lower=D.max(), upper=10000)
    observation = pm.DiscreteUniform("obs", lower=1, upper=N, observed=D)

### Mysterious code to be explained in Chapter 3.
with german_tank_model:
    step = pm.Metropolis()
    trace = pm.sample(40000, tune=10000, chains=1, step=step, return_inferencedata=False)

N_samples = trace['N']

# histogram of the samples:

plt.hist(N_samples, density = True)
plt.show()
