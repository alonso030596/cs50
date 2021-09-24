while True:
    height = int(input("Height:"))
    if height >= 1 and height <= 8:
        break

gap = "  "

for i in range(0, height):
    #First spaces
    for j in range (height - i -1, 0, -1):
        print(" ", end = "")
    #First pyramid
    for k in range (0, i + 1):
        print("#", end = "")
    #Gap
    print(gap, end = "")
    #Second pyramid
    for l in range (0, i + 1):
        print("#", end = "")
    #New row
    print("")
