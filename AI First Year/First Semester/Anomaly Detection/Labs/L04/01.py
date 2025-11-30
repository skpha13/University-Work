from pyod.utils import generate_data
from pyod.models.ocsvm import OCSVM
from pyod.models.deep_svdd import DeepSVDD

from sklearn.metrics import balanced_accuracy_score, roc_auc_score

import matplotlib.pyplot as plt

CONTAMINATION = 0.15

X_train, X_test, y_train, y_test = generate_data(
    n_train=300, n_test=200, n_features=3, contamination=CONTAMINATION, random_state=42
)


def run_and_plot_model(
    model_class,
    model_kwargs,
    fig_name,
    ax_titles=None,
):
    model = model_class(**model_kwargs)
    model.fit(X_train, y_train)
    y_train_pred = model.predict(X_train)
    y_test_pred = model.predict(X_test)
    scores = model.decision_function(X_test)

    ba = balanced_accuracy_score(y_test, y_test_pred)
    roc_auc = roc_auc_score(y_test, scores)
    print(f"BA: {ba}\nROC AUC: {roc_auc}\n")

    fig = plt.figure(figsize=(16, 12), layout="constrained")
    titles = ax_titles or [
        "Ground Truth (Train)",
        "Ground Truth (Test)",
        "Predicted Labels (Train)",
        "Predicted Labels (Test)",
    ]
    # gt (train)
    ax1 = fig.add_subplot(221, projection="3d")
    ax1.set_title(titles[0])
    for label, color, name in zip([0, 1], ["b", "r"], ["Inlier", "Outlier"]):
        ax1.scatter(
            X_train[y_train == label, 0],
            X_train[y_train == label, 1],
            X_train[y_train == label, 2],
            c=color,
            label=name,
            alpha=0.6,
        )
    ax1.legend()

    # gt (test)
    ax2 = fig.add_subplot(222, projection="3d")
    ax2.set_title(titles[1])
    for label, color, name in zip([0, 1], ["b", "r"], ["Inlier", "Outlier"]):
        ax2.scatter(
            X_test[y_test == label, 0],
            X_test[y_test == label, 1],
            X_test[y_test == label, 2],
            c=color,
            label=name,
            alpha=0.6,
        )
    ax2.legend()

    # predicted labels (train)
    ax3 = fig.add_subplot(223, projection="3d")
    ax3.set_title(titles[2])
    for label, color, name in zip([0, 1], ["b", "r"], ["Inlier", "Outlier"]):
        ax3.scatter(
            X_train[y_train_pred == label, 0],
            X_train[y_train_pred == label, 1],
            X_train[y_train_pred == label, 2],
            c=color,
            label=name,
            alpha=0.6,
        )
    ax3.legend()

    # predicted labels (test)
    ax4 = fig.add_subplot(224, projection="3d")
    ax4.set_title(titles[3])
    for label, color, name in zip([0, 1], ["b", "r"], ["Inlier", "Outlier"]):
        ax4.scatter(
            X_test[y_test_pred == label, 0],
            X_test[y_test_pred == label, 1],
            X_test[y_test_pred == label, 2],
            c=color,
            label=name,
            alpha=0.6,
        )
    ax4.legend()

    plt.savefig(fig_name)
    plt.close(fig)


if __name__ == "__main__":
    run_and_plot_model(
        OCSVM,
        {"kernel": "linear", "contamination": CONTAMINATION},
        fig_name="./pdfs/01_linear.pdf",
    )
    run_and_plot_model(
        OCSVM,
        {"kernel": "rbf", "contamination": CONTAMINATION},
        fig_name="./pdfs/01_rbf.pdf",
    )
    run_and_plot_model(
        DeepSVDD,
        {"n_features": 3, "contamination": CONTAMINATION, "random_state": 42},
        fig_name="./pdfs/01_deep_svdd.pdf",
    )
