import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Load the dataset
data = np.loadtxt('YearPredictionMSD.txt', delimiter=',')

# Split the data into features and labels
X = data[:, 1:]  # Exclude the year column
y = data[:, 0]  # First column is the target label (year)

# Extract the MFCC averages and covariances
mfcc_covariances = X[:, 12:90]

# Calculate the average covariance heatmap
avg_covariance = np.mean(mfcc_covariances, axis=0).reshape(13, 78 // 12)
avg_covariance_df = pd.DataFrame(avg_covariance, columns=[f'cov_{i}' for i in range(1, 79 // 12 + 1)])

# Display the average MFCC covariance heatmap
plt.figure(figsize=(10, 4))
sns.heatmap(avg_covariance_df, annot=True, fmt='.2f', cmap='coolwarm', center=0)
plt.title('Average MFCC Covariance Heatmap')
plt.xlabel('Covariance Index')
plt.ylabel('MFCC Average Index')
plt.show()