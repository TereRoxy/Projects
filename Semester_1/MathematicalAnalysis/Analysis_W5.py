# Terebent Roxana

import pandas as pd
import openpyxl


def gradient_descent(x: float, eta: float) -> float:
    res = x - eta * f_prime(x)
    return res


def f_of_x(x: float):
    return x**2


def f_prime(x: float) -> float:
    return 2*x


def computations(no_iterations: int, x1: float, eta: float) -> float:
    for i in range(no_iterations):
        x1 = gradient_descent(x1, eta)
    return x1


iterations = [1, 5, 10, 15, 20, 50]
x_values = [1, 5, 10, 15, 20, 50]
eta_values = [0.001, 0.01, 0.1, 1, 10, 100]
iteration_list = []
result_list = []
starting_list = []
eta_list = []

for eta_val in eta_values:
    for x_val in x_values:
        for it in iterations:
            result = computations(it, x_val, eta_val)
            result_list.append(result)
            iteration_list.append(it)
            starting_list.append(x_val)
            eta_list.append(eta_val)


result_df = pd.DataFrame({"Number of Iterations": iteration_list,
                          "Initial Value of x": starting_list, "Value Chosen for eta": eta_list,
                          "Obtained Value": result_list})
result_df.to_excel("output_results_Terebent_Roxana_1.xlsx", index=False)
