# Terebent Roxana Alexandra

import numpy as np
import matplotlib.pyplot as plt


def set_bounds(bounds: list) -> list:   # used for the computations
    bounds.append(100)
    bounds.append(200)
    bounds.append(500)
    bounds.append(1000)
    bounds.append(2000)
    bounds.append(3000)
    bounds.append(5000)
    bounds.append(10000)
    bounds.append(20000)
    bounds.append(30000)
    bounds.append(50000)
    return bounds


def generate_lists(bounds: list):   # the lists of positive and negative elements
    for i in range(1, 2 * bounds[len(bounds)-1]+10):
        if i % 2 == 1:
            positives.append(1/i)
        else:
            negatives.append(-1/i)


# computes the sum of the series
def sum_list(bounds: list, terms_pos: list, terms_neg: list, p: int, q: int) -> list:
    results = []
    # length = 0
    for j in range(0, len(bounds)):
        sum_value = 0
        length = bounds[j]
        i = 0
        index_pos = 0
        index_neg = 0
        while i < length:
            for k in range(0, p):
                sum_value += terms_pos[index_pos]
                index_pos += 1
            for k in range(0, q):
                sum_value += terms_neg[index_neg]
                index_neg += 1
            i += p + q
        results.append(sum_value)
    return results


def show_results(results: list, bounds: list):
    print("The sum of the series after the indicated number of elements is: ")
    for i in range(0, len(bounds)):
        print(str(bounds[i]) + " elements: " + str(results[i]))



positives = []
negatives = []

number_elements = []
number_elements = set_bounds(number_elements)
generate_lists(number_elements)
p = 1
q = 1

results = sum_list(number_elements, positives, negatives, p, q)

show_results(results, number_elements)

print("The limit of the series alternating " + str(p) + " positive and " + str(q) + " negative elements is: ")
print(results[len(results)-1])


# plot the graph
X = np.array(number_elements)
Y = np.array(sum_list(number_elements, positives, negatives, 1, 1))
plt.scatter(X, Y)
plt.show()
