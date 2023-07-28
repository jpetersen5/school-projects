import sqlite3
import csv

conn = sqlite3.connect('results.db')

cursor = conn.cursor()

cursor.execute('''CREATE TABLE your_table (
                    column1 datatype,
                    column2 datatype,
                    ...
                  )''')

with open('YearPredictionMSD.txt', 'r') as file:
    csv_reader = csv.reader(file)
    for row in csv_reader:
        cursor.execute("INSERT INTO your_table VALUES (?, ?, ...)", row)

conn.commit()
conn.close()
