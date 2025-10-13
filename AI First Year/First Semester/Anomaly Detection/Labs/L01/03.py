import numpy as np
import matplotlib.pyplot as plt

from pyod.utils.data import generate_data
from sklearn.metrics import confusion_matrix

CONTAMINATION_RATE = 0.1

X_train, X_test, y_train, y_test = samples = generate_data(n_train=1000, n_test=0, n_features=2, contamination=CONTAMINATION_RATE, random_state=42)

mean = np.mean(X_train, axis=0)
std = np.std(X_train, axis=0)
z_scores = np.abs(X_train - mean) / std

quantile_90 = np.quantile(z_scores, q=0.9)
predicted_anomalies = z_scores > quantile_90
is_anomaly = np.any(predicted_anomalies, axis=1)

plt.figure()
plt.scatter(X_train[~is_anomaly, 0], X_train[~is_anomaly, 1],
            c="blue", label="Normal", alpha=0.6, s=20)
plt.scatter(X_train[is_anomaly, 0], X_train[is_anomaly, 1],
            c="red", label="Anomalies (90th quantile)", alpha=0.8, s=50, marker="x")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.title("Predicted Anomalies (90th Quantile Method)")
plt.legend()
plt.grid(True)
plt.savefig("./03.pdf")

c_matrix = confusion_matrix(y_train, is_anomaly)
TN = c_matrix[1][1]
TP = c_matrix[0][0]
FN = c_matrix[0][1] 
FP = c_matrix[1][0]
TNR = TN / (TN + FP)
TPR = TP / (TP + FN)
BA = (TPR + TNR) / 2

print(f"BA: {BA}")