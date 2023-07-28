import pandas as pd
from sklearn.experimental import enable_hist_gradient_boosting
from sklearn.ensemble import HistGradientBoostingClassifier
from sklearn.inspection import permutation_importance
from sklearn.metrics import classification_report, precision_recall_curve, auc, roc_curve
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('creditcard.csv')

X = df.drop('Class', axis=1)
y = df['Class']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = HistGradientBoostingClassifier()

num_runs = 100
accuracies = []
auprcs = []
tree_depths = []
importances_all = np.zeros(X.shape[1])

for _ in range(num_runs):
    model.fit(X_train, y_train)

    accuracy = model.score(X_test, y_test)
    accuracies.append(accuracy)

    y_pred_proba = model.predict_proba(X_test)[:, 1]
    precision, recall, thresholds = precision_recall_curve(y_test, y_pred_proba)
    auprc = auc(recall, precision)
    auprcs.append(auprc)

    num_trees = model.n_iter_
    max_depth = np.log2(num_trees + 1)  # Estimate using log2(num_trees + 1)
    tree_depths.append(max_depth)

    result = permutation_importance(model, X_test, y_test, n_repeats=10, random_state=42)
    importances = result.importances_mean
    importances_all += importances

average_accuracy = np.mean(accuracies)
average_auprc = np.mean(auprcs)
average_tree_depth = np.mean(tree_depths)
importances_all /= num_runs

feature_names = X.columns.tolist()
feature_importance = dict(zip(feature_names, importances_all))
sorted_feature_importance = sorted(feature_importance.items(), key=lambda x: x[1], reverse=True)

plt.figure(figsize=(8, 6))
features, importances = zip(*sorted_feature_importance)
plt.barh(features, importances)
plt.xlabel('Average Feature Importance')
plt.ylabel('Features')
plt.title('Average Feature Importances')
plt.tight_layout()
plt.savefig('average_feature_importances.png')

plt.figure(figsize=(8, 6))
plt.plot(recall, precision, label='AUPRC curve (area = %0.2f)' % average_auprc)
plt.xlabel('Recall')
plt.ylabel('Precision')
plt.title('Average Precision-Recall Curve')
plt.legend(loc='lower right')
plt.tight_layout()
plt.savefig('average_prc_curve.png')

print(f"Average Accuracy: {average_accuracy}")
print(f"Average AUPRC: {average_auprc}")
print(f"Estimated Tree Depth: {average_tree_depth}")
