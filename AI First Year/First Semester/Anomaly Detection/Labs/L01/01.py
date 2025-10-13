import matplotlib.pyplot as plt

from pyod.utils.data import generate_data

X_train, X_test, y_train, y_test = samples = generate_data(n_train=400, n_test=100, n_features=2, contamination=0.1)

plt.figure(figsize=(10, 6))
plt.scatter(X_train[y_train == 0, 0], X_train[y_train == 0, 1], c="blue", label="Normal (Train)", alpha=0.6)
plt.scatter(X_train[y_train == 1, 0], X_train[y_train == 1, 1], c="red", label="Outliers (Train)", alpha=0.8, marker="x")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.title("Normal Data vs Outliers")
plt.legend()
plt.grid(True)
plt.savefig("./01.pdf")