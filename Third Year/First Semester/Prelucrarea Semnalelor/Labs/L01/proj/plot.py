import matplotlib.pyplot as plt
import numpy as np
import os

# create folder if it does not exist
os.makedirs("./plots", exist_ok=True)

def plot(name: str, x: np.ndarray, y: np.ndarray):
    fig, ax = plt.subplots()
    fig.suptitle(name)
    ax.plot(x, y)
    plt.savefig(fname=f"./plots/{name}.pdf", format="pdf")
    plt.show()

def stem(name: str, x: np.ndarray, y: np.ndarray):
    fig, ax = plt.subplots()
    fig.suptitle(name)
    ax.stem(x, y)
    plt.savefig(fname=f"./plots/{name}.pdf", format="pdf")
    plt.show()