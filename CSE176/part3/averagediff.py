import sqlite3
import numpy as np

conn_results = sqlite3.connect('results.db')
cursor_results = conn_results.cursor()

query = 'SELECT "V14 for Class 0", "V14 for Class 1" FROM v14_results'
cursor_results.execute(query)
results = cursor_results.fetchall()

differences = [result[0] - result[1] for result in results if result[0] is not None]

average_difference = np.mean(differences)

print(f"Average Difference: {average_difference}")

conn_results.close()
