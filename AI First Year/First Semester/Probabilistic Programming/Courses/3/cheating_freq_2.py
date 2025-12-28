import pymc as pm
from matplotlib import pyplot as plt


N = 100

with pm.Model() as model:
    p = pm.Uniform("freq_cheating", 0, 1)
    p_skewed = pm.Deterministic("p_skewed", 0.5*p + 0.25)

X = 35

with model:
    yes_responses = pm.Binomial("number_cheaters", 100, p_skewed, observed=35)

with model:
    step = pm.Metropolis()
    trace = pm.sample(40000, tune=10000, step=step, chains=1, return_inferencedata=False)

p_trace = trace["freq_cheating"]

plt.hist(p_trace, histtype="stepfilled", density=True, alpha=0.85, bins=30,
         label="posterior distribution", color="#348ABD")
plt.vlines([.05, .35], [0, 0], [5, 5], alpha=0.2)
plt.xlim(0, 1)
plt.legend()

plt.show()



