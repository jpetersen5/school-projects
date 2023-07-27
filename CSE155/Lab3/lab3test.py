num = input()
prime = False
for i in range(1, int(num)):
    if(int(num) == 2):
        print("test")
        prime = False
        break
    if(int(num) % i == 0):
        test = i
        if((i != num) and (i != 1)):
            prime = False
            break
if(prime == True):
    print(num + " is a prime number\n")
else: 
    print(num + " is not a prime number!!!!\n")