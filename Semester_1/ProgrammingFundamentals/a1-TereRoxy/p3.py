# Solve the problem from the third set here
# Generate the largest perfect number smaller than a given natural number n.
# If such a number does not exist, a message should be displayed.
# A number is perfect if it is equal to the sum of its divisors, except itself.(e.g. 6 is a perfect number, as 6=1+2+3).

def search_number(x: int) -> int:
    while True and x > 6:
        x = x - 1
        if is_perfect(x):
            return x
        else:
            continue
    return 0


def is_perfect(x: int) -> bool:
    sdiv = 1
    d = 2
    while d * d < x:
        if x % d == 0:
            sdiv = sdiv + d + x / d
        d = d + 1
    if d * d == x:
        sdiv = sdiv + d
    if sdiv == x:
        return True
    else:
        return False


def read_input() -> int:
    x = int(input(">>> "))
    return x


about_message = "This program generates the largest perfect number smaller than a given natural number n.\nA number is perfect if it is equal to the sum of its' divisors except itself."
print(about_message)
print("Please enter your number:")
n = read_input()
ans = search_number(n)
if ans:
    print(ans)
else:
    print("No perfect number smaller than:", n)
