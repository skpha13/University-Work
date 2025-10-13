import matplotlib.pyplot as plt

from pyod.utils.data import generate_data

from pyod.models.knn import KNN
from sklearn.metrics import confusion_matrix
from sklearn.metrics import roc_curve

CONTAMINATION_RATE = 0.1

X_train, X_test, y_train, y_test = samples = generate_data(n_train=400, n_test=100, n_features=2, contamination=CONTAMINATION_RATE, random_state=42)

model = KNN(contamination=CONTAMINATION_RATE)
model.fit(X_train, y_train)
predictions = model.predict(X_test)

c_matrix = confusion_matrix(y_test, predictions)
TN = c_matrix[1][1]
TP = c_matrix[0][0]
FN = c_matrix[0][1] 
FP = c_matrix[1][0]
print(f"TN: {TN}\tTP: {TP}\tFN: {FN}\tFP: {FP}")

fpr, tpr, thresholds = roc_curve(y_test, predictions)
plt.figure()
plt.plot(fpr, tpr, color="darkorange", label="ROC curve")
plt.plot([0, 1], [0, 1], color="navy", linestyle="--")
plt.xlabel("False Positive Rate")
plt.ylabel("True Positive Rate")
plt.title("Receiver Operating Characteristic (ROC) Curve")
plt.legend(loc="lower right")
plt.grid(True)
plt.savefig("./02.pdf")