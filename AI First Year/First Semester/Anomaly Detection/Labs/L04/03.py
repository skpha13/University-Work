from scipy.io import loadmat
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import balanced_accuracy_score, roc_auc_score

from pyod.models.ocsvm import OCSVM
from pyod.models.deep_svdd import DeepSVDD

data = loadmat("./data/shuttle.mat")
X = data["X"]
y = data["y"].flatten()

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.5, random_state=42, stratify=y
)

scaler = StandardScaler()
X_train_std = scaler.fit_transform(X_train)
X_test_std = scaler.transform(X_test)

svm = OCSVM()
svm.fit(X_train_std, y_train)
y_pred_svm = svm.predict(X_test_std)
ba_svm = balanced_accuracy_score(y_test, y_pred_svm)
roc_svm = roc_auc_score(y_test, svm.decision_function(X_test_std))
print(f"OCSVM BA: {ba_svm:.4f}, ROC AUC: {roc_svm:.4f}")

architectures = [
    [32, 16],
    [64, 32],
    [128, 64, 32],
]

for i, arch in enumerate(architectures):
    svdd = DeepSVDD(n_features=9, hidden_neurons=arch, epochs=20, verbose=0)
    svdd.fit(X_train_std, y_train)
    y_pred_svdd = svdd.predict(X_test_std)
    ba_svdd = balanced_accuracy_score(y_test, y_pred_svdd)
    test_scores_svdd = svdd.decision_function(X_test_std)
    roc_svdd = roc_auc_score(y_test, test_scores_svdd)
    print(f"DeepSVDD Arch {arch}: BA: {ba_svdd:.4f}, ROC AUC: {roc_svdd:.4f}")
