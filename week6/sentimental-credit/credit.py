while True:
    try:
        number = int(input("Number: "))
        break
    except:
        continue

str_number = str(number)
length = len(str_number)

# Luhn’s Algorithm
# Step 1 : Multiply every other digit by 2, starting with the number’s second-to-last digit,
# and then add those products’ digits together.
SumEveryTwox2 = 0
for i in range(1, length, 2):
    EveryTwox2 = int(str_number[length-i-1])*2

    if EveryTwox2 < 10:
        SumEveryTwox2 = SumEveryTwox2 + EveryTwox2
    else:
        str_tens = str(EveryTwox2)
        SmallSum = 1 + int(str_tens[1])
        SumEveryTwox2 = SumEveryTwox2 + SmallSum

# Step 2 : Add the sum to the sum of the digits that weren’t multiplied by 2.
SumEveryOtherTwo = 0
for j in range(0, length, 2):
    EveryOtherTwo = int(str_number[length-j-1])
    SumEveryOtherTwo = SumEveryOtherTwo + EveryOtherTwo

# Step 3 : Add the two sums from the Luhn’s Algorithm
verify_number = SumEveryTwox2 + SumEveryOtherTwo

# Step 4 : Condition if card number is valid, AMEX, Mastercard or Visa
if ((verify_number % 10) != 0):
    print("INVALID")
    exit(0)

# First & first2 digit
first = int(number / pow(10, length - 1))
first2 = int(number / pow(10, length - 2))

if length == 15 and (first2 == 34 or first2 == 37):
    print("AMEX")
elif length == 16 and (first2 == 51 or first2 == 52 or first2 == 53 or first2 == 54 or first2 == 55):
    print("MASTERCARD")
elif (length == 13 or length == 16) and first == 4:
    print("VISA")
else:
    print("INVALID")