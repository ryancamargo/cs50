from cs50 import get_float

# Get the change owed from the user
while True:
    change = get_float("Change: ")
    if change > 0:
        break

# Multiplying the dollar value for 100 to get the cents value and rounding it to nearest integer
x = round(change * 100)

# Calculate the minimum number of coins

i = 0

while x > 0:
    if x >= 25:
        x -= 25
        i += 1
    elif x >= 10:
        x -= 10
        i += 1
    elif x >= 5:
        x -= 5
        i += 1
    else:
        x -= 1
        i += 1

print(i)
