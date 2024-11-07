import pickle
import random

import networkx
import numpy as np
from matplotlib import pyplot as plt

from power_method import power_method

seed = 0
np.random.seed(seed)
random.seed(seed)

A = np.random.randint(100, size=(6, 6))
eigen_vector, eigen_value = power_method(A, 1000)
r_np = np.linalg.eig(A)

print(f"Eigen Vector: {eigen_vector}\nEigen Value: {eigen_value}")

print(f"Numpy eigen vectors:\n{r_np.eigenvectors}")
print(f"Numpy eigen value:\n{r_np.eigenvalues}")
print()

eps = 1e-5
with open("./data/graphs.pickle", "rb") as file:
    graphs = pickle.load(file)

    for graph in graphs:
        G = networkx.convert_matrix.from_numpy_array(graph)
        networkx.draw(G, with_labels=True)
        plt.show()

    for index, graph in enumerate(graphs):
        eigens = np.linalg.eig(graph)
        converted_graph = networkx.convert_matrix.from_numpy_array(graph)
        largest_clique = networkx.algorithms.approximation.clique.max_clique(converted_graph)

        eigen_values = np.unique(np.round(eigens.eigenvalues, 3))

        print(f"GRAPH {index}:\nEigen Values: {eigen_values}")
        print(f"IS Complete: {len(eigen_values) == 2}")
        print(f"Largest Clique: {largest_clique}")
        print(
            f"IS Bipartite: {-1 * max(eigens.eigenvalues) - eps <= min(eigens.eigenvalues) <= -1 * max(eigens.eigenvalues) + eps}"
        )
        print()
