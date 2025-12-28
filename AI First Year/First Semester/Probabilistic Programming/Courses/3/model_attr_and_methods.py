import pymc as pm
import numpy as np

RANDOM_SEED = 8927
rng = np.random.default_rng(RANDOM_SEED)

with pm.Model() as model:
    mu = pm.Normal("mu", mu=0, sigma=1)
    obs = pm.Normal("obs", mu=mu, sigma=1, observed=rng.standard_normal(100))

print(model.basic_RVs)                    # [Output]: [mu ~ N(0, 1), obs ~ N(mu, 1)]
print(model.free_RVs)                     # [Output]: [mu ~ N(0, 1)]
print(model.observed_RVs)                 # [Output]: [obs ~ N(mu, 1)]
print(model.compile_logp()({"mu": 0}))    # [Output]: array(-143.03962875)
