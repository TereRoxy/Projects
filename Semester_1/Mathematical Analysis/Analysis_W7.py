# TEREBENT ROXANA
#  Compute with the trapezoidal rule the integral of e^(-x^2) from -inf to inf in increasing bounds of integration.

import numpy as np
import texttable


def get_partitions(first_x, last_x, N):

    # Height of the trapeziums, or dx
    h = (last_x - first_x) / N
    return [first_x + i*h for i in range(N+1)]


def f(x):
    return np.exp(-x**2)


def integral(a, b, n):
    """
    Compute the integral of f from a to b using the trapezoidal rule with n intervals.
    :param a: lower bound of integration
    :param b: upper bound of integration
    :param n: number of intervals
    :return: integral of f from a to b
    """
    # div = np.linspace(a, b, n)
    div = get_partitions(a, b, n)
    h = (b - a) / n

    # implement the trapezoidal rule from scratch
    sigma = 0
    for xi in range(1, n):
        sigma += (f(div[xi-1]) + f(div[xi])) * h/2
    return sigma
    # return np.trapz(f(div), div)


def show_table(a, b, n):
    table = texttable.Texttable()
    table.set_deco(texttable.Texttable.HEADER)
    table.set_cols_dtype(['i', 'f', 'f'])
    table.set_cols_align(["c", "c", "c"])
    table.add_rows([["n", "integral", "error"]])
    for i in range(1, n):
        table.add_row([i, integral(a, b, i), abs(integral(a, b, i) - np.sqrt(np.pi))])
    print(table.draw())


def main():
    for i in range(1, 10):
        print("\n")
        show_table(-i, i, 2*i)


if __name__ == '__main__':
    main()
