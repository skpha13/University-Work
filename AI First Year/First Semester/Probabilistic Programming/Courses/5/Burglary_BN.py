import pymc as pm
import numpy as np

with pm.Model() as model:
    B = pm.Bernoulli("B", 0.001)
    E = pm.Bernoulli("E", 0.002)

    p_A = pm.math.switch(B, pm.math.switch(E, .95, .94), pm.math.switch(E, .29, 0.001))
    A = pm.Bernoulli("A", p_A)

    p_J = pm.math.switch(A, .9, .05)
    J = pm.Bernoulli('J', p_J, observed = 1)

    p_M = pm.math.switch(A, .7, .01)
    M = pm.Bernoulli('M', p_M, observed = 1)

with model:
    step = pm.BinaryGibbsMetropolis(vars=[B, E, A])
    trace = pm.sample(40000, step=step, tune=10000, return_inferencedata=False, chains=1)


B_samples = trace["B"]

print()
print()
print("Burglary probability:", B_samples.mean())



