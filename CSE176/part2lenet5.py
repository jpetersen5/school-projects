import xgboost as xgb
import numpy as np
import scipy.io
from sklearn.preprocessing import LabelEncoder
#from sklearn.model_selection import train_test_split
from sklearn import metrics
import matplotlib.pyplot as plt
import seaborn as sns
import time
start_time = time.time()

# Load the MNIST dataset
mnist = scipy.io.loadmat('MNIST-LeNet5.mat')
X_train = mnist['train_fea']
Y_train = mnist['train_gnd'].T.flatten()
X_test = mnist['test_fea']
Y_test = mnist['test_gnd'].T.flatten()

# Train-test split
#X_train, X_val, Y_train, Y_val = train_test_split(X, Y, test_size=0.1, random_state=42)
le = LabelEncoder()
Y_train = le.fit_transform(Y_train)
Y_test = le.transform(Y_test)
#Y_val = le.transform(Y_val)

# Parameter grid
params = {
    'max_depth': 9,
    'learning_rate': 0.1,
    'objective': 'multi:softmax',
    'n_estimators':2500,
    'num_class': 10,
    'min_child_weight': 1,
    'gamma': 0,
    'subsample': 1,
    'colsample_bytree': 1,
    'n_jobs': -1,
    'random_state': 42,
    'eval_metric': 'merror',  # Classification error (1 - accuracy)
}

# XGBoost classifier
clf = xgb.XGBClassifier(**params)
clf.fit(
    X_train, Y_train,
    eval_set=[(X_test, Y_test)],
    verbose=True
)

# Evaluate the classifier on the test set
Y_pred = clf.predict(X_test)
Y_pred = le.inverse_transform(Y_pred)
Y_test = le.inverse_transform(Y_test)

# Extract the number of trees and performance metrics
n_trees = clf.n_estimators
test_errors = clf.evals_result()['validation_0']['merror'][:n_trees]
#val_errors = clf.evals_result()['validation_1']['merror'][:n_trees]
min_test_error_idx = np.argmin(test_errors)
min_test_error = test_errors[min_test_error_idx]
#min_val_error_idx = np.argmin(val_errors)
#min_val_error = val_errors[min_val_error_idx]

# Calculate & sort top 20 feature importance
feature_importances = clf.feature_importances_
top_n = 20
top_feature_indices = np.argsort(feature_importances)[-top_n:]
top_feature_importances = feature_importances[top_feature_indices]

# Find the best test error and its index
best_test_error = min(test_errors)
best_num_trees = test_errors.index(best_test_error) + 1

# Accuracy reports
accuracy = metrics.accuracy_score(Y_test, Y_pred)
print("Test set accuracy:", accuracy)
print(metrics.classification_report(Y_test, Y_pred))
print("r squared score:",metrics.r2_score(Y_test, Y_pred))
print("mean squared log error:",metrics.mean_squared_log_error(Y_test, Y_pred))

# Time it took to fit the model
print(time.time() - start_time)

# Validation / Training error as a function of # of trees
plt.plot(np.arange(1, n_trees + 1), test_errors, label='Testing error')
plt.axhline(y=min_test_error, color='r', linestyle='--', label='Minimum testing error')
plt.axvline(x=min_test_error_idx, color='r', linestyle='--')
plt.xlabel('Number of trees')
plt.ylabel('Error')
plt.legend()
plt.title('Testing Error vs. Number of Trees')
plt.savefig('test_error_vs_num_trees_lenet5.eps', format='eps')
plt.show()

# Confusion matrix heatmap
cm = metrics.confusion_matrix(Y_test, Y_pred)
plt.figure(figsize=(10, 10))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', cbar=False)
plt.xlabel('Predicted Label')
plt.ylabel('True Label')
plt.title('Confusion Matrix')
plt.show()

# Generate the bar graph of the top 20 feature importances
plt.figure(figsize=(10, 5))
plt.bar(range(top_n), top_feature_importances, align='center')
plt.xticks(range(top_n), top_feature_indices, rotation=90)
plt.xlabel('Feature Index')
plt.ylabel('Importance')
plt.title('Top 20 Feature Importances')
plt.show()