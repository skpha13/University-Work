import numpy as np
from sklearn.metrics import confusion_matrix

SIZE = 2

mean = np.random.random(size=(SIZE, 1))
L = np.random.normal(0, 0.01, size=(SIZE, SIZE))
E = L @ L.T
C = np.linalg.cholesky(E)

x = np.random.normal(0, 1, size=(SIZE, SIZE))

y = C @ x + mean.reshape(1, -1)

z_scores = None
quantile_90 = np.quantile(z_scores, 0.9)

is_anomaly = z_scores > quantile_90

print(mean.shape)
print(E.shape)
print(x.shape)
print()
print(z_scores.shape)
print(quantile_90.shape)
print(is_anomaly.shape)

c_matrix = confusion_matrix(y, is_anomaly)
TN = c_matrix[1][1]
TP = c_matrix[0][0]
FN = c_matrix[0][1] 
FP = c_matrix[1][0]
TNR = TN / (TN + FP)
TPR = TP / (TP + FN)
BA = (TPR + TNR) / 2

print(f"BA: {BA}")

