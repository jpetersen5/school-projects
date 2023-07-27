import math

print("Prime detector\nEnter a number to begin: ")
num = int(input())

while (num != 0):
    prime = 1
    for i in range(2, int(math.sqrt(num)) + 1):
        if (num % i == 0):
            prime = 0
            break
    if (prime):
        print(str(num) + " is a prime.")
    else:
        print(str(num) + " is not a prime.")
    num = int(input())
