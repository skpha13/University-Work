import numpy as np
from sklearn.metrics import confusion_matrix

SIZE = 2

mean = np.random.random(size=(SIZE, 1))
L = np.random.normal(0, 0.01, size=(SIZE, SIZE))
E = L @ L.T # ensure positive semi-definite
C = np.linalg.cholesky(E)

x = np.random.normal(0, 1, size=(SIZE, SIZE))
y = C @ x + mean # our samples

# solve liniar system
diff = y - mean
system_sol = np.linalg.solve(E, diff)

# compute z-scores for each column and apply 90th quantile on it
z_scores = (y - mean).T @ system_sol
quantile_90 = np.quantile(z_scores, 0.9, axis=0)

is_anomaly = z_scores > quantile_90

y_true = np.array([[0, 1],[0, 0]]).flatten() # placeholder values
y_pred = is_anomaly.astype(int).flatten()

c_matrix = confusion_matrix(y_true, y_pred)
TN = c_matrix[1][1]
TP = c_matrix[0][0]
FN = c_matrix[0][1] 
FP = c_matrix[1][0]
TNR = TN / (TN + FP)
TPR = TP / (TP + FN)
BA = (TPR + TNR) / 2

print(f"BA: {BA}")

