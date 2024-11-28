import os
import random
from typing import Literal

import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.metrics import ConfusionMatrixDisplay, accuracy_score, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC

os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)

seed = 0
random.seed(seed)

iris = load_iris()

X_train, X_test, y_train, y_test = train_test_split(
    iris.data, iris.target, test_size=50, random_state=seed, shuffle=True
)


def fit_predict(filename: str, kernel: Literal["linear", "poly", "rbf", "sigmoid", "precomputed"] = "linear"):
    clf = SVC(kernel=kernel)
    clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)

    cm = confusion_matrix(y_test, y_pred, labels=clf.classes_)

    print(f"Accuracy: {accuracy:.2f}")
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=iris.target_names)
    disp.plot(cmap="hot")
    plt.savefig(f"./plots/{filename}.png", format="png")
    plt.show()


fit_predict("confusion_matrix_linear", "linear")
fit_predict("confusion_matrix_rbf", "rbf")
