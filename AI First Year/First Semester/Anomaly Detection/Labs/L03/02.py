from sklearn.datasets import make_blobs
from pyod.models.iforest import IForest
from pyod.models.dif import DIF
from pyod.models.loda import LODA

import matplotlib.pyplot as plt

import numpy as np
import torch
import random

np.random.seed(0)
torch.manual_seed(0)
random.seed(0)


X_1, _ = make_blobs(
    n_samples=500, centers=[(0, 10)], cluster_std=1, n_features=2, random_state=42
)
X_2, _ = make_blobs(
    n_samples=500, centers=[(10, 0)], cluster_std=1, n_features=2, random_state=42
)

X = np.concatenate([X_1, X_2])
test = np.random.uniform(-10, 20, size=(1000, 2))

models = {
    "Isolation Forest": IForest(contamination=0.2, random_state=42),
    "DIF": DIF(
        contamination=0.2, random_state=42, hidden_neurons=[64, 128, 256, 128, 64]
    ),
    "LODA": LODA(contamination=0.2, n_bins=50),
}

fig, axes = plt.subplots(1, 3, figsize=(18, 6), constrained_layout=True)

for ax, (name, model) in zip(axes, models.items()):
    model.fit(X)
    scores = model.decision_function(test)

    anomaly_scores = -scores
    anomaly_scores = (anomaly_scores - anomaly_scores.min()) / (
        anomaly_scores.max() - anomaly_scores.min()
    )

    sc = ax.scatter(
        test[:, 0],
        test[:, 1],
        c=anomaly_scores,
        cmap="inferno",
        s=40,
        label="Test samples",
    )
    ax.set_title(name)
    ax.set_xlabel("x1")
    ax.set_ylabel("x2")

plt.suptitle("Comparison of PyOD Models: IForest vs DIF vs LODA", fontsize=16)
plt.savefig("./pdfs/02.pdf")

# 5. The data is projected onto 1D lines, and the decision if a point belongs in the dataset happens on one of those lines.
# So we basically linearly cut the dataset.
