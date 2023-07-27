def findChange(value, availableQuarters, availableDimes, availableNickles, availablePennies):
    value = float(value)
    availableQuarters = int(availableQuarters)
    availableDimes = int(availableDimes)
    availableNickles = int(availableNickles)
    availablePennies = int(availablePennies)
    numQuarters = 0
    numDimes = 0
    numNickles = 0
    numPennies = 0
    while (value >= 0.25 and availableQuarters > 0):
        value = round(value - 0.25,2)
        numQuarters = numQuarters + 1
        availableQuarters = availableQuarters - 1
    while (value >= 0.10 and availableDimes > 0):
        value = round(value - 0.10,2)
        numDimes = numDimes + 1
        availableDimes = availableDimes - 1
    while (value >= 0.05 and availableNickles > 0):
        value = round(value - 0.05,2)
        numNickles = numNickles + 1
        availableNickles = availableNickles - 1
    while (value > 0 and availablePennies > 0):
        value = round(value - 0.01,2)
        numPennies = numPennies + 1
        availablePennies = availablePennies - 1
    if(value == 0):
        #print("numQuarters: " + str(numQuarters))
        #print("numDimes: " + str(numDimes))
        #print("numNickles: " + str(numNickles))
        #print("numPennies: " + str(numPennies))
        return (True, {"quarter":numQuarters,"dime":numDimes,"nickel":numNickles,"penny":numPennies}, value)
    #print("can not reach the total value with available change")
    return (False, {"quarter":numQuarters,"dime":numDimes,"nickel":numNickles,"penny":numPennies}, value)