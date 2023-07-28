import numpy as np
import matplotlib.pyplot as plt
from sklearn.experimental import enable_hist_gradient_boosting
from sklearn.ensemble import HistGradientBoostingRegressor
from sklearn.inspection import permutation_importance
from sklearn.model_selection import GridSearchCV, train_test_split
from sklearn.metrics import mean_squared_error, r2_score

data = np.loadtxt('YearPredictionMSD.txt', delimiter=',')

X = data[:, 1:]  
y = data[:, 0]  

X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=463715, test_size=51630, shuffle=False)

regressor = HistGradientBoostingRegressor()

param_grid = {
    'learning_rate': [0.5, 0.1, 0.],
    'max_iter': [1000, 500, 100],
    'max_leaf_nodes': [10, 20, 30],
    'min_samples_leaf': [2, 4, 6],
}

grid_search = GridSearchCV(regressor, param_grid, cv=3, scoring='neg_mean_squared_error')
grid_search.fit(X_test, y_test)

best_params = grid_search.best_params_
best_score = -grid_search.best_score_

print("Best Parameters:", best_params)
print("Best Score (MSE):", best_score)

regressor = HistGradientBoostingRegressor(**best_params)
regressor.fit(X_train, y_train)

y_pred = regressor.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)
print("Test MSE:", mse)
print("R-squared:", r2)

plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred, s=5)
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'k--', lw=2)
plt.xlabel('Actual')
plt.ylabel('Predicted')
plt.title('Predicted vs Actual')
plt.savefig('predicted_vs_actual.png')
