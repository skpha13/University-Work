import numpy as np
import pymc as pm
from matplotlib import pyplot as plt


# The parameters to be inferred. We only know them here because we are synthesising the data.
true_alpha = 10
true_beta = 50

num_flashes = 5000

# Generate the angles
true_thetas = np.random.uniform(low=-0.5*np.pi, high=0.5*np.pi, size=num_flashes)

# Generate the x coordinates of the flashes along the coastline
data = true_alpha + true_beta * np.tan(true_thetas)

def obs_logp(value, alpha, beta):
    return pm.math.sum(pm.math.log(beta) - pm.math.log(np.pi) - pm.math.log(beta**2 + (alpha-value)**2))

with pm.Model() as lighthouse_model:
    alpha = pm.Normal("alpha", mu = 0, tau = 1.0/50**2)
    beta = pm.Exponential("beta", lam = 1.0/100)

    # We have a prior distribution for the angle of the lighthouse for every time we observed a flash, uniform over [-pi/2, pi/2]
    thetas = pm.Uniform("thetas", lower=-0.5*np.pi, upper=0.5*np.pi, size=num_flashes)

    obs = pm.CustomDist(
        'obs',
        alpha, beta,
        logp=obs_logp,
        observed = data
    )

with lighthouse_model:
    step = pm.NUTS()
    trace = pm.sample(40000, tune=10000, step=step, chains=1, return_inferencedata=False)

alpha_samples = trace["alpha"]
beta_samples = trace["beta"]

# histogram of the samples:

plt.hist(alpha_samples, density = True)
plt.show()

plt.hist(beta_samples, density = True)
plt.show()
