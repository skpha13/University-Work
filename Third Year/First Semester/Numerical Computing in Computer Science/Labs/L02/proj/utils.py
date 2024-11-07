import os

import networkx
import numpy as np
from matplotlib import pyplot as plt

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)


def power_method(matrix: np.ndarray, max_iterations: int = 1000, tolerance: float = 1e-6):
    error = 1
    iterations = 0

    y = np.random.rand(len(matrix))
    y = np.divide(y, np.linalg.norm(y))

    while error > tolerance:
        if iterations > max_iterations:
            break

        z = np.dot(matrix, y)
        z = np.divide(z, np.linalg.norm(z))

        error = np.linalg.norm(z - y)

        y = z
        iterations += 1

    eigen_value = np.dot(y, np.dot(matrix, y)) / np.dot(y, y)
    return y, eigen_value


def plot_graph(fname: str, graph: networkx.classes.graph.Graph) -> None:
    networkx.draw(graph, with_labels=True)

    plt.savefig(f"./plots/{fname}.png", format="png")
    plt.show()
