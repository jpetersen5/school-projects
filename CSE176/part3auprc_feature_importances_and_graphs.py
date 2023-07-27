import pandas as pd
from sklearn.experimental import enable_hist_gradient_boosting
from sklearn.ensemble import HistGradientBoostingClassifier
from sklearn.inspection import permutation_importance
from sklearn.metrics import classification_report, precision_recall_curve, auc
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

df = pd.read_csv('creditcard.csv')

X = df.drop('Class', axis=1)
y = df['Class']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = HistGradientBoostingClassifier()
model.fit(X_train, y_train)

result = permutation_importance(model, X_test, y_test, n_repeats=10, random_state=42)
importance = result.importances_mean
feature_names = X.columns.tolist()
feature_importance = dict(zip(feature_names, importance))
sorted_feature_importance = sorted(feature_importance.items(), key=lambda x: x[1], reverse=True)

plt.figure(figsize=(8, 6))
features, importances = zip(*sorted_feature_importance)
plt.barh(features, importances)
plt.xlabel('feature fmportance')
plt.ylabel('features')
plt.title('feature importances')
plt.tight_layout()
plt.savefig('featurs.png')

y_pred = model.predict(X_test)

accuracy = model.score(X_test, y_test)

precision, recall, thresholds = precision_recall_curve(y_test, y_pred)
auprc = auc(recall, precision)

plt.figure(figsize=(8, 6))
plt.plot(recall, precision, color='b', lw=2, label='prc')
plt.xlabel('Re-shit')
plt.ylabel('Pre-cum')
plt.title('Precision-Recall Curve')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('prc.png')

print(f"accuracy: {accuracy}")
print(f"auprc: {auprc}")

classification_rep = classification_report(y_test, y_pred, output_dict=True)
classification_rep_df = pd.DataFrame(classification_rep).transpose()
classification_rep_df.drop(columns=['support'], inplace=True)
classification_rep_df.plot(kind='bar', figsize=(8, 6))
plt.xlabel('Class')
plt.ylabel('Score')
plt.title('Classification Report')
plt.tight_layout()
plt.savefig('awful.png')

classification_rep_df.to_csv('shitreportsoidonthavetoprint2console.csv', index=True)
