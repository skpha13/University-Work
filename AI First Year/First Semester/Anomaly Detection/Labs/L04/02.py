from scipy.io import loadmat
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.svm import OneClassSVM
from sklearn.metrics import balanced_accuracy_score

data = loadmat("./data/cardio.mat")
X = data["X"]
y_pyod = data["y"].flatten()
y = 1 - 2 * y_pyod

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.6, random_state=42, stratify=y
)

pipeline = Pipeline([("scaler", StandardScaler()), ("ocsvm", OneClassSVM())])

param_grid = {
    "ocsvm__kernel": ["rbf", "sigmoid", "linear"],
    "ocsvm__gamma": ["scale", "auto", 0.001, 0.01, 0.1, 1],
    "ocsvm__nu": [0.01, 0.05, 0.15, 0.2, 0.25, 0.3],
}

grid = GridSearchCV(
    pipeline, param_grid, scoring="balanced_accuracy", cv=5, n_jobs=-1, verbose=2
)
grid.fit(X_train, y_train)

print("Best parameters found:", grid.best_params_)

y_pred = grid.best_estimator_.predict(X_test)
test_ba = balanced_accuracy_score(y_test, y_pred)
print("Balanced Accuracy on Test set:", test_ba)
