from scipy.io import loadmat
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import balanced_accuracy_score, roc_auc_score

from pyod.models.iforest import IForest
from pyod.models.dif import DIF
from pyod.models.loda import LODA

from tqdm import tqdm

import numpy as np
import torch
import random

import warnings

warnings.filterwarnings("ignore")


np.random.seed(0)
torch.manual_seed(0)
random.seed(0)

data = loadmat("./data/shuttle.mat")
X = data["X"]
y = data["y"].ravel()

models = {
    "Isolation Forest": IForest(random_state=42),
    "DIF": DIF(random_state=42),
    "LODA": LODA(n_bins=10),
}

n_runs = 10
results = {name: {"BA": [], "ROC_AUC": []} for name in models.keys()}

for run in tqdm(range(n_runs)):
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.4, random_state=run
    )

    scaler = StandardScaler().fit(X_train)
    X_train_scaled = scaler.transform(X_train)
    X_test_scaled = scaler.transform(X_test)

    for name, model in models.items():
        model.fit(X_train_scaled)

        y_pred = model.predict(X_test_scaled)
        y_scores = model.decision_function(X_test_scaled)

        ba = balanced_accuracy_score(y_test, y_pred)
        roc_auc = roc_auc_score(y_test, y_scores)

        results[name]["BA"].append(ba)
        results[name]["ROC_AUC"].append(roc_auc)


print("Mean Balanced Accuracy and ROC AUC over 10 runs")
for name in models.keys():
    mean_ba = np.mean(results[name]["BA"])
    std_ba = np.std(results[name]["BA"])
    mean_auc = np.mean(results[name]["ROC_AUC"])
    std_auc = np.std(results[name]["ROC_AUC"])

    print(
        f"{name:20s} | BA: {mean_ba:.3f} ± {std_ba:.3f} | ROC AUC: {mean_auc:.3f} ± {std_auc:.3f}"
    )
