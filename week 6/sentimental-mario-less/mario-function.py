from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        break

#i = 1

#for n in range(1, 9):
#    if n == 1:
#        print("#")
#    for n >= i:
#        print(" ")
#        print("#")
#        i = i + 1
#    break


for i in range(0, n, 1):
    for j in range(0, n, 1):
        if (i + j < n - 1):
            print(" ", end="")
        else:
            print("#", end="")
    print()
