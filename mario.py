from cs50 import get_int

def main():
    n = get_positive_int()
    print_pyramid(n)

def get_positive_int():
    while True:
       n = get_int("Height:")
       if n < 9 and n > 0:
           break
    return n

def print_pyramid(n):
    for i in range(n):
        for j in range(n-(i+1)):
            print(" ", end="")
        print("#" * (i+1), end="")
        print("  ", end="")
        print("#" * (i+1))

main()