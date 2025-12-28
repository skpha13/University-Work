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

with pm.Model() as lighthouse_model:
    alpha = pm.Normal("alpha", mu = 0, tau = 1.0/50**2)
    beta = pm.Exponential("beta", lam = 1.0/100)

    # We have a prior distribution for the angle of the lighthouse for every time we observed a flash, uniform over [-pi/2, pi/2]
    thetas = pm.Uniform("thetas", lower=-0.5*np.pi, upper=0.5*np.pi, size=num_flashes)
    xs = alpha + beta * pm.math.tan(thetas)

    obs = pm.Normal("obs", mu = xs, sigma = 0.01, observed = data)

with lighthouse_model:
    step = pm.Metropolis()
    trace = pm.sample(5000, tune=1000, step=step, chains=1, return_inferencedata=False)

alpha_samples = trace["alpha"]
beta_samples = trace["beta"]

# histogram of the samples:

plt.hist(alpha_samples, density = True)
plt.show()

plt.hist(beta_samples, density = True)
plt.show()
