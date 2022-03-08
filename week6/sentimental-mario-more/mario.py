# Mario More

# Import get_int form CS50 library
from cs50 import get_int

# Loop to reprompt for the pyramid if int < 1 or > 8
while True:
    height = get_int("Height : ")
    if height > 0 and height < 9:
        break

# Loop for the different floor of the pyramid
for x in range(height):
    # Loop for the space before the left half
    for y in range(height - (x+1)):
        print(" ", end="")
    # Loop for the bricks of the left half
    for y in range(x+1):
        print("#", end="")
    # Printing the two spaces between left and right half
    print("  ", end="")
    # Loop for the bricks of the right half
    for y in range(x+1):
        print("#", end="")
    # Print a new line for a new floor
    print()