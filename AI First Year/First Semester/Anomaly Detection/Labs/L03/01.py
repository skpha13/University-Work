import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.utils.fixes import np

X, _ = make_blobs(
    n_samples=500, center_box=(0, 0), cluster_std=1, n_features=2, random_state=42
)

projections = np.random.multivariate_normal(mean=[0, 0], cov=np.eye(2), size=5)
projections = projections / np.linalg.norm(projections, axis=1, keepdims=True)

num_bins = 10
histograms = []
bin_edges_list = []

for v in projections:
    projected = X @ v
    hist, bin_edges = np.histogram(
        projected, bins=num_bins, range=(-5, 5), density=False
    )
    prob = hist / hist.sum()
    histograms.append(prob)
    bin_edges_list.append(bin_edges)


X_test = np.random.uniform(-3, 3, size=(500, 2))

scores = []
for x in X_test:
    probs = []
    for i, v in enumerate(projections):
        proj_val = np.dot(x, v)
        bins = bin_edges_list[i]
        bin_idx = np.digitize(proj_val, bins) - 1
        if 0 <= bin_idx < len(histograms[i]):
            p = histograms[i][bin_idx]
        else:
            p = 0
        probs.append(p)
    score = np.mean(probs)
    scores.append(score)

scores = np.array(scores)

plt.figure(figsize=(7, 6))
plt.scatter(X_test[:, 0], X_test[:, 1], c=scores, cmap="inferno", s=40)
plt.colorbar(label="Mean Probability")
plt.title(f"LODA-like anomaly detection (bins={num_bins})")
plt.xlabel("x1")
plt.ylabel("x2")
plt.savefig(f"./pdfs/01.pdf")
