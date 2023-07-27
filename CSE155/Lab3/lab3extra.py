from math import sqrt
from sys import maxsize

for num in range(1, maxsize):
    prime = 1
    for i in range(2, int(sqrt(num)) + 1):
        if (num % i == 0):
            prime = 0
            break
    if (prime):
        print(num)
