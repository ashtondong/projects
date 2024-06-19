def main():
    height = get_height()
    n = 1
    for i in range(height):
        for j in range(height - n):
            print(" ", end="")
        for k in range(height - (height - n)):
            print("#", end="")
        print()
        n += 1


def get_height():  # defining a height function to continously prompt the user for a height
    while True:
        try:  # to prevent user from entering a non-integer
            height = int(input("Height: \n"))
            if height > 0:
                return height
        except:
            print("Not an integer.")


main()