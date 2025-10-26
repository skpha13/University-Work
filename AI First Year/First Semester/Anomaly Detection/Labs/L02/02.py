import matplotlib.pyplot as plt

from pyod.utils.data import generate_data_clusters
from pyod.models.knn import KNN
from sklearn.metrics import balanced_accuracy_score

import warnings

warnings.filterwarnings("ignore")

X_train, X_test, y_train, y_test = generate_data_clusters(
    400, 200, 2, 2, 0.1, random_state=1
)

nns = [3, 5, 7, 9]
best_nn = 0
best_ba = 0

for nn in nns:
    model = KNN(contamination=0.1, n_neighbors=nn)
    model.fit(X_train)
    y_pred = model.predict(X_test)

    ba = balanced_accuracy_score(y_test, y_pred)
    print(f"N: {nn}, BA: {ba:.4f}")

    if ba >= best_ba:
        best_ba = ba
        best_nn = nn

model = KNN(contamination=0.1, n_neighbors=best_nn)
model.fit(X_train, y_train)
y_train_pred = model.predict(X_train)
y_pred = model.predict(X_test)

fig, axes = plt.subplots(2, 2, figsize=(10, 10))
titles = [
    "Ground Truth (Train)",
    "Predicted Labels (Train)",
    "Ground Truth (Test)",
    "Predicted Labels (Test)",
]
data_sets = [
    (X_train, y_train),
    (X_train, y_train_pred),
    (X_test, y_test),
    (X_test, y_pred),
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
plt.savefig("./pdfs/02.pdf")
