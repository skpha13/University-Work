import numpy as np
import matplotlib.pyplot as plt
from pyod.models.knn import KNN
from sklearn.datasets import make_blobs
from pyod.models.lof import LOF

RANDOM_STATE = 42

X_200, _ = make_blobs(
    n_samples=200, center_box=(-10, 10), cluster_std=2, random_state=RANDOM_STATE
)
X_100, _ = make_blobs(
    n_samples=100, center_box=(10, 10), cluster_std=6, random_state=RANDOM_STATE
)
X = np.concatenate((X_200, X_100))

knn = KNN(contamination=0.07, n_neighbors=5)
knn.fit(X)
y_pred_knn = knn.predict(X)

lof = LOF(n_neighbors=5, contamination=0.07)
lof.fit(X)
y_pred_lof = lof.predict(X)

fig, axes = plt.subplots(1, 2, figsize=(10, 5))

titles = [
    "KNN",
    "LOF",
]
data_sets = [
    (X, y_pred_knn),
    (X, y_pred_lof),
]

for ax, (X, y), title in zip(axes.ravel(), data_sets, titles):
    inliers = X[y == 0]
    outliers = X[y == 1]
    ax.scatter(inliers[:, 0], inliers[:, 1], c="blue", label="Inliers", s=20, alpha=0.6)
    ax.scatter(
        outliers[:, 0], outliers[:, 1], c="red", label="Outliers", s=20, alpha=0.6
    )
    ax.set_title(title)
    ax.legend(loc="upper right")

plt.tight_layout()
plt.savefig("./pdfs/03.pdf")
