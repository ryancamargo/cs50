x = int(input("x: "))
y = int(input("y: "))

z = x / y
print(z)

# floating-point imprecision  --->  print(f"{z:.50f}")  is still happening
# integer overflow is not a problem in python  \o/
