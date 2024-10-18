import matplotlib.pyplot as plt
import numpy as np
import scipy

data = np.genfromtxt("regresie.csv", delimiter=",")

A = data[:, 0]
A = np.column_stack((A, np.ones(len(data))))
b = data[:, 1]

x, _, _, _ = scipy.linalg.lstsq(A, b)
alpha = x[0]
beta = x[1]

samples = np.linspace(data[:, 0].min(), data[:, 0].max(), 256)
results = alpha * samples + beta

plt.scatter(data[:, 0], data[:, 1], marker="x")
plt.plot(samples, results, "m", label=f"Line: y = {alpha:.2f}x + {beta:.2f}")
plt.xlabel("z")
plt.ylabel("w")
plt.title("Scatter Plot")
plt.show()
