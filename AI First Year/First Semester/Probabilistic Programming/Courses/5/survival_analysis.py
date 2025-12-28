import numpy as np
import pymc as pm
from matplotlib import pyplot as plt

N = 20

#create some artificial data. 

with pm.Model():
    tmp = pm.Weibull("tmp", alpha = 2, beta = 5)

lifetime = pm.draw(tmp, draws=N)
birth = np.random.uniform(0, 10, N)

censor = (birth + lifetime) > 10 #an individual is right-censored if this is True 
lifetime_ = lifetime.copy()
lifetime_[censor] = 10 - birth[censor] #we only see this part of their lives.
                       
with pm.Model() as survive_model:
    alpha = pm.Uniform("alpha", 0,20) 
    #lets just use uninformative priors 
    beta = pm.Uniform("beta", 0,20) 

    obs = pm.Weibull( 'obs', alpha = alpha, beta = beta, observed = lifetime_)

    potential = pm.Potential("obs_censor", pm.math.log(pm.math.switch(censor, 0.2, 1)))

with survive_model:

    # Use the default NUTS for sampling
    trace = pm.sample(50000, tune=30000, return_inferencedata=False, chains=1)

alpha_samples = trace['alpha']
beta_samples = trace['beta']

# histogram of the samples:

plt.hist(alpha_samples, density = True)
plt.show()
plt.hist(beta_samples, density = True)
plt.show()

medianlifetime_samples = beta_samples * (np.log(2)**(1 / alpha_samples))

plt.hist(medianlifetime_samples, density = True)
plt.show()
