import pymc as pm
import numpy as np
import pytensor.tensor as at
from matplotlib import pyplot as plt


N = 100
X = 35

with pm.Model() as model:
    p = pm.Uniform("freq_cheating", 0, 1)
    true_answers = pm.Bernoulli("truths", p, shape=N, initval=np.random.binomial(1, 0.5, N))
    first_coin_flips = pm.Bernoulli("first_flips", 0.5, shape=N, initval=np.random.binomial(1, 0.5, N))
    second_coin_flips = pm.Bernoulli("second_flips", 0.5, shape=N, initval=np.random.binomial(1, 0.5, N))
    val = first_coin_flips*true_answers + (1 - first_coin_flips)*second_coin_flips
    observed_proportion = pm.Deterministic("observed_proportion", at.sum(val)/float(N))
    observations = pm.Binomial("obs", N, observed_proportion, observed=X)

with model:
    step = pm.Metropolis(vars=[p])
    trace = pm.sample(40000, tune=10000, step=step, chains=1, return_inferencedata=False)

p_trace = trace["freq_cheating"]

plt.hist(p_trace, histtype="stepfilled", density=True, alpha=0.85, bins=30,
         label="posterior distribution", color="#348ABD")
plt.vlines([.05, .35], [0, 0], [5, 5], alpha=0.3)
plt.xlim(0, 1)
plt.legend()

plt.show()



