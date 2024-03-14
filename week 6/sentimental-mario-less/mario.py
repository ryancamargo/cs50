from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        break

if n == 1:
    print("#")

if n == 2:
    print(" #")
    print("##")

if n == 3:
    print("  #")
    print(" ##")
    print("###")

if n == 4:
    print("   #")
    print("  ##")
    print(" ###")
    print("####")

if n == 5:
    print("    #")
    print("   ##")
    print("  ###")
    print(" ####")
    print("#####")

if n == 6:
    print("     #")
    print("    ##")
    print("   ###")
    print("  ####")
    print(" #####")
    print("######")

if n == 7:
    print("      #")
    print("     ##")
    print("    ###")
    print("   ####")
    print("  #####")
    print(" ######")
    print("#######")

if n == 8:
    print("       #")
    print("      ##")
    print("     ###")
    print("    ####")
    print("   #####")
    print("  ######")
    print(" #######")
    print("########")



