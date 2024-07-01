# Solve the problem from the first set here
# Problem 1: Generate the first prime number larger than a given natural number n.

def is_prime(x: int) -> bool:
    if x < 2:
        return False
    if x == 2:
        return True
    if x % 2 == 0:
        return False
    d = 3
    for d in range(3, d*d <= x, 2):
        if x % d == 0:
            return False

    return True


def search_number(x: int) -> int:
    while True:
        x = x+1
        if is_prime(x):
            return x
        else:
            continue


print("This program generates the first prime number larger than a given natural number n")

while True:
    print("Please enter your number: ")
    n = int(input(">>> "))
    if type(n) == int:
        print(search_number(n))

    else:
        print("Invalid input. Please try again")
        continue
