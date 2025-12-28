import pymc as pm
import graphviz as gv
import numpy as np
import matplotlib.pyplot as plt

true_head_p = 0.7

n = 1000

obs = np.random.binomial(n, true_head_p)

with pm.Model() as coin_model:
    p = pm.Uniform('p')
    res = pm.Binomial('res', n, p, observed=obs)

gv = pm.model_to_graphviz(coin_model)
gv.format = 'png'
gv.render(filename = 'model_graph')

### Mysterious code to be explained in Chapter 3.
with coin_model:
    step = pm.Metropolis()
    trace = pm.sample(40000, tune=10000, chains=1, step=step, return_inferencedata=False)

p_samples = trace['p']

plt.hist(p_samples, bins = 40)
plt.show()
