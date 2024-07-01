# 2. Dynamic Programming
# Given the set of positive integers S and the natural number k, display one of the subsets of S which sum to k.
# For example, if S = { 2, 3, 5, 7, 8 } and k = 14, subset { 2, 5, 7 } sums to 14.

def read_input(n: int) -> list:
    numbers = [0]
    for i in range(1, n+1):
        x = int(input())
        numbers.append(x)
    return numbers


def build_sum(k: int, numbers: list) -> list:
    smax = 0    # current maximum sum of the elements
    dp = [0] * (k + 1)   # marks the values being used to build a sum
    res = [0] * (k + 1)     # marks the last element added to the sum

    # we build an array of possible sums using the input list
    for i in range(1, len(numbers)):
        for j in range(smax, -1, -1):   # for the current number, we try to add it to the previous numbers in the list
            if dp[j]:   # if the sum j can be obtained
                if j + numbers[i] <= k:    # if we can add the current number to the previous sum
                    dp[j + numbers[i]] = 1  # we mark the sum as being obtained
                    res[j + numbers[i]] = numbers[i]   # we mark the last element added to the sum
                    smax = max(smax, (j + numbers[i]))    # we update the maximum sum obtained until now

        if numbers[i] <= k and dp[numbers[i]] == 0:     # if the current number is smaller than the sum we want to get
            dp[numbers[i]] = 1  # we mark the number as used
            res[numbers[i]] = numbers[i]
            smax = max(smax, numbers[i])

    print("Intermediate data structures used for result in dynamic programming: ")
    print("Possible sums: ", dp)
    print("Last added element to obtain the sum", res)
    return res


def reconstruct_solution(part_res: list, k: int):
    if part_res[k] == 0:    # if the sum cannot be obtained
        print("No solution")
        return
    sol = []
    i = k   # we start from the last element in the sum (which is the total)
    while i > 0:    # at each step, we add to the solution the previous element added to the sum
        # the previous elem is the partial sum up until the element
        sol.append(part_res[i])
        i -= part_res[i]
    sol.reverse()   # make it in increasing order
    print("Solution: ")
    print(sol)


def naive_solution(k: int, start_idx: int, numbers: list, sol: list):
    # backtracking solution
    """
    This function computes all the decompositions of number k as a sum of numbers in a given list
        :param k: number to be decomposed
        :param start_idx: keeps track of the current index of the number being considered in the list
        :param numbers: given list of numbers
        :param sol: the list where it constructs the solution
        :return:
    """
    if k == 0:  # if we reached a solution
        print("Naive solution: ", sol)
        return

    for i in range(start_idx, len(numbers)):  # search for the number that could lead to a solution
        if numbers[i] not in sol:   # if the number is not already in the solution
            if numbers[i] <= k:  # if valid
                sol.append(numbers[i])  # add to the solution list
                naive_solution(k - numbers[i], i, numbers, sol)  # decomposes the difference n - number added
                sol.pop()  # deletes number when the function backtracks
            else:
                break
    return


print("Please enter the number of values S has: ")
n = int(input(">>> "))
print("Please enter the values: ")
values = read_input(n)

print("Please enter the sum you want to get: ")
k = int(input(">>> "))

naive_solution(k, 1, values, [])

result = build_sum(k, values)
reconstruct_solution(result, k)
