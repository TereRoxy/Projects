# Solve the problem from the second set here
# The numbers n1 and n2 have the property P if their writing in base 10 uses the same digits (e.g. 2113 and 323121).
# Determine whether two given natural numbers have property P.

def parse_digits(x: int, digits: list):
    while x:
        if x % 10 not in digits:
            digits.append(x % 10)
        x = int(x / 10)


def read_input() -> int:
    x = int(input(">>> "))
    return x

about_message = "This program determines whether two given natural numbers have the property P.\nTwo numbers have property P if they use the same digits in their base 10 representation."
print(about_message)

print("Please enter the first number: ")
n1 = read_input()
print("Please enter the second number: ")
n2 = read_input()

digits_n1 = []
digits_n2 = []

parse_digits(n1, digits_n1)
parse_digits(n2, digits_n2)

digits_n1.sort()
digits_n2.sort()

if digits_n1 == digits_n2:
    print("The numbers have property P")
else:
    print("The numbers don't have property P")
