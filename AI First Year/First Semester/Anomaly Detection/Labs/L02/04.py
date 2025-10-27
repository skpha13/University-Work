import numpy as np
import scipy

from sklearn.metrics import balanced_accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from pyod.models.knn import KNN
from pyod.utils.utility import standardizer
from pyod.models.combination import maximization

data = scipy.io.loadmat("./data/cardio.mat")

X = data["X"]
y = data["y"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42
)
X_train = MinMaxScaler().fit_transform(X_train)
X_test = MinMaxScaler().fit_transform(X_test)

nns = np.linspace(start=30, stop=120, num=10).astype(np.uint8)
models = []
y_train_pred = []
y_test_pred = []
train_scores = []
test_scores = []
for nn in nns:
    model = KNN(n_neighbors=nn)
    model.fit(X_train)
    models.append(model)

    y_train_pred.append(model.predict(X_train))
    y_test_pred.append(model.predict(X_test))

    train_scores.append(model.decision_scores_)
    test_scores.append(model.decision_function(X_test))

    print(f"{nn}-NN BA TRAIN: {balanced_accuracy_score(y_train, y_train_pred[-1]):.4f}")
    print(f"{nn}-NN BA  TEST: {balanced_accuracy_score(y_test, y_test_pred[-1]):.4f}")
    print()

train_scores = np.array(train_scores).T  # (n_samples, n_models)
test_scores = np.array(test_scores).T  # (n_samples, n_models)
train_scores_norm = standardizer(train_scores)
test_scores_norm = standardizer(test_scores)
combined_train_max = maximization(train_scores_norm)
combined_test_max = maximization(test_scores_norm)

threshold_train = np.quantile(combined_train_max, q=0.80)
threshold_test = np.quantile(combined_test_max, q=0.80)

ensemble_train_pred = combined_train_max >= threshold_train
ensemble_test_pred = combined_test_max >= threshold_test

print(
    f"Ensemble KNN BA TRAIN: {balanced_accuracy_score(y_train, ensemble_train_pred):.4f}"
)
print(
    f"Ensemble KNN BA  TEST: {balanced_accuracy_score(y_test, ensemble_test_pred):.4f}"
)
