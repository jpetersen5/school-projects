import numpy as np
import matplotlib.pyplot as plt
from sklearn.experimental import enable_hist_gradient_boosting
from sklearn.ensemble import HistGradientBoostingRegressor
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.model_selection import train_test_split

# Load the dataset
data = np.loadtxt('YearPredictionMSD.txt', delimiter=',')

# Split the data into features and labels
X = data[:, 1:]  # Exclude the year column
y = data[:, 0]  # First column is the target label (year)

# Split the data into train and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=463715, test_size=51630, shuffle=False)

# Define the regressor
regressor = HistGradientBoostingRegressor()

# Define the parameter grid for tuning
param_grid = {
    'learning_rate': [0.04],
    'max_iter': [1000],
    'max_leaf_nodes': [150],
    'max_depth': [6],
    'min_samples_leaf': [20],
}

# Perform grid search to find the best parameters
grid_search = GridSearchCV(regressor, param_grid, cv=3, scoring='neg_mean_squared_error')
grid_search.fit(X_train, y_train)

# Get the best parameters and best score
best_params = grid_search.best_params_
best_score = -grid_search.best_score_

print("Best Parameters:", best_params)
print("Best Score (MSE):", best_score)

# Train the regressor with the best parameters
regressor = HistGradientBoostingRegressor(**best_params)
regressor.fit(X_train, y_train)

# Predict on the test set
y_pred = regressor.predict(X_test)

# Calculate the mean squared error and R-squared score
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)
print("Test MSE:", mse)
print("R-squared:", r2)

# Plot the predicted vs actual values
plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred, s=5)
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'k--', lw=2)
plt.xlabel('Actual')
plt.ylabel('Predicted')
plt.title('Predicted vs Actual')
plt.savefig('predicted_vs_actual.png')
