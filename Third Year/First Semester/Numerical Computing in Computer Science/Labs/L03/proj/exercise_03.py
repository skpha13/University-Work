import os

import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

iris = datasets.load_iris()

iris_data = iris.data
scaler = StandardScaler()
iris_standardized = scaler.fit_transform(iris_data)

pca = PCA(n_components=2)
components = pca.fit_transform(iris_standardized)
print(components)

fig, ax = plt.subplots(1)
fig.suptitle("PCA componenets")
ax.scatter(components[:, 0], components[:, 1])
plt.savefig(f"./plots/pca_components.png", format="png")
plt.show()
