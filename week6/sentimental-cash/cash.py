from cs50 import get_float

# Loop to repromt user for a non-negative float
while True:
    change = get_float("Change owde: ")
    if change >= 0:
        break

# Calculate number of quarters (25¢), and updating the change
numQuarters = int(change / 0.25)
change = round(change - numQuarters * 0.25, 2)

# Calculate number of dimes (10¢), and updating the change
numDimes = int(change / 0.10)
change = round(change - numDimes * 0.10, 2)

# Calculate number of nickels (5¢), and updating the change
numNickels = int(change / 0.05)
change = round(change - numNickels * 0.05, 2)

# Calculate number of pennies (1¢), and updating the change
numPennies = int(change / 0.01)

# Print the minumun number of coin required to give the change
print(numQuarters + numDimes + numNickels + numPennies)

