import matplotlib.pyplot as plt
import numpy as np
import pymc as pm

data = np.random.normal(0, 1, 1000)

def normal_sim(rng, a, b, size=1000):
    return rng.normal(a, b, size=size)

with pm.Model() as abc_model:
    a = pm.Normal("a", mu=0, sigma=5)
    b = pm.HalfNormal("b", sigma=1)
    s = pm.Simulator("s", normal_sim, params=(a, b), sum_stat="sort", epsilon=1, observed=data)

    trace = pm.sample_smc(chains=1, return_inferencedata=False)

a_samples = trace['a']
b_samples = trace['b']


# histogram of the samples:

plt.hist(a_samples, density = True)
plt.show()

plt.hist(b_samples, density = True)
plt.show()
