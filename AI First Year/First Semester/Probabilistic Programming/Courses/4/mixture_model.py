import numpy as np
import pymc as pm
import scipy.stats as stats
import pytensor.tensor as pt
import pytensor
import arviz as az
from matplotlib import pyplot as plt
import matplotlib as mpl

data = np.loadtxt("mixture_data.csv", delimiter=",")

plt.hist(data, bins=20, color="k", histtype="stepfilled", alpha=0.8)
plt.title("Histogram of the dataset")
plt.ylim([0, None])
plt.show()

with pm.Model() as model:
    p1 = pm.Uniform('p', 0, 1)
    p2 = 1 - p1
    p = pt.stack([p1, p2])
    assignment = pm.Categorical("assignment", p, 
                                shape=data.shape[0],
                                initval=np.random.randint(0, 2, data.shape[0]))
    
with model:
    sds = pm.Uniform("sds", 0, 100, shape=2)
    # form new API, may use the sigma/tau for paramter tau = 1/(sigma**2), 
    # the sd is not supported anymore in Normal
    # https://www.pymc.io/projects/docs/en/stable/api/distributions/generated/pymc.Normal.html
    centers = pm.Normal("centers", 
                        mu=np.array([120, 190]), 
                        sigma=np.array([10., 10.]), 
                        shape=2)
    
    center_i = pm.Deterministic('center_i', centers[assignment])
    sd_i = pm.Deterministic('sd_i', sds[assignment])
    
    # and to combine it with the observations:
    observations = pm.Normal("obs", mu=center_i, sigma=sd_i, observed=data)
    
pytensor.config.compute_test_value = 'off'

with model:
    # We use the CategoricalGibbsMetropolis, and return_inferencedata=False here for compatibility.
    step1 = pm.Metropolis(vars=[p1,sds, centers])
    step2 = pm.CategoricalGibbsMetropolis(vars=[assignment])
    trace1 = pm.sample(25000, step=[step1, step2],return_inferencedata=False,tune=5000,chains=1)
    
    # Use the default NUTS for sampling, and we return the Arviz InferenceData
    step3 = pm.CategoricalGibbsMetropolis(vars=[assignment])
    trace2 = pm.sample(25000, step=[step3],tune=5000,chains=1)

plt.subplot(311)
lw = 1
center_trace = trace1["centers"]

# for pretty colors later in the book.
colors = ["#348ABD", "#A60628"] if center_trace[-1, 0] > center_trace[-1, 1] \
    else ["#A60628", "#348ABD"]

plt.plot(center_trace[:, 0], label="trace of center 0", c=colors[0], lw=lw)
plt.plot(center_trace[:, 1], label="trace of center 1", c=colors[1], lw=lw)
plt.title("Traces of unknown parameters")
leg = plt.legend(loc="upper right")
leg.get_frame().set_alpha(0.7)

plt.subplot(312)
std_trace = trace1["sds"]
plt.plot(std_trace[:, 0], label="trace of standard deviation of cluster 0",
     c=colors[0], lw=lw)
plt.plot(std_trace[:, 1], label="trace of standard deviation of cluster 1",
     c=colors[1], lw=lw)
plt.legend(loc="upper left")

plt.subplot(313)
p_trace = trace1["p"]
plt.plot(p_trace, label="$p$: frequency of assignment to cluster 0",
     color=colors[0], lw=lw)
plt.xlabel("Steps")
plt.ylim(0, 1)
plt.legend()
plt.show()

az.plot_trace(trace2.posterior.centers,figsize=(20, 4))
az.plot_trace(trace2.posterior.sds,figsize=(20, 4))
az.plot_trace(trace2.posterior.p,figsize=(20, 4))
plt.show()

_i = [1, 2, 3, 4]
for i in range(2):
    plt.subplot(2, 2, _i[2 * i])
    plt.title("Posterior of center of cluster %d" % i)
    plt.hist(center_trace[:, i], color=colors[i], bins=30,
             histtype="stepfilled")

    plt.subplot(2, 2, _i[2 * i + 1])
    plt.title("Posterior of standard deviation of cluster %d" % i)
    plt.hist(std_trace[:, i], color=colors[i], bins=30,
             histtype="stepfilled")
    # plt.autoscale(tight=True)

plt.tight_layout()
plt.show()


norm_pdf = stats.norm.pdf
x = 175

v = p_trace * norm_pdf(x, loc=center_trace[:, 0], scale=std_trace[:, 0]) > \
    (1 - p_trace) * norm_pdf(x, loc=center_trace[:, 1], scale=std_trace[:, 1])

print("Probability of belonging to cluster 0:", v.mean())

