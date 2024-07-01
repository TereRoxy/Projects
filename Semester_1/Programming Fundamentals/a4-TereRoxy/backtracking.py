# 1. Backtracking
# Consider a positive number n. Determine all its decompositions as sums of prime numbers.
from math import sqrt


def is_prime(x: int) -> bool:
    if x < 2:
        return False
    if x == 2:
        return True
    if x % 2 == 0:
        return False
    for d in range(3, int(sqrt(x))+1, 2):
        if x % d == 0:
            return False
    return True


# creates a list of prime numbers smaller or equal to n
def create_sieve(upper_bound: int) -> list:
    sieve = [2]
    for cnt in range(3, upper_bound+1, 2):
        if is_prime(cnt):
            sieve.append(cnt)

    return sieve


def prime_decompositions_rec(n: int, start_idx: int, primes: list, sol: list):
    """
    This function computes all the decompositions of number n as sums of prime numbers
    :param n: number to be decomposed
    :param start_idx: keeps track of the current index of the prime number being considered in the list
    :param primes: array of prime numbers it uses to decompose the solution
    :param sol: the list where it constructs the solution
    :return:
    """
    if n == 0:  # if we reached a solution
        print_solution(sol)
        return

    for i in range(start_idx, len(primes)):     # search for the prime number that could lead to a solution
        if primes[i] <= n:      # if valid
            sol.append(primes[i])   # add to the solution list
            prime_decompositions_rec(n-primes[i], i, primes, sol)   # decomposes the difference n - number added
            sol.pop()   # deletes number when the function backtracks
        else:       # stops the search as the next numbers won't lead to a solution
            break
    return


def prime_decompositions_it(n: int, primes: list):
    stack = [(n, 0, [])]  # (remaining number, index of current prime, solution)

    while stack:
        num, prime_idx, sol = stack.pop()

        if num == 0:
            print_solution(sol)

        for i in range(prime_idx, len(primes)):
            prime = primes[i]
            if prime <= num:
                new_sol = sol + [prime]     # to be added to the stack
                stack.append((num - prime, i, new_sol))

            else:
                break


def print_solution(solution: list):
    print_string = "= "
    for i in range(0, len(solution)-1):
        print_string += str(solution[i])
        print_string += " + "
    print_string += str(solution[len(sol)-1])
    print(print_string)


while True:
    print("Please enter a number:")
    n = int(input(">>> "))
    primes = create_sieve(n)
    sol = []
    # prime_decompositions_rec(n, 0, primes, sol)
    prime_decompositions_it(n, primes)
