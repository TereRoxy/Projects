# permutation sort
# heap sort

import random
import time


def generate_numbers(n: int) -> list:
    arr = []
    for i in range(0, n):
        x = random.randrange(0, 100)
        arr.append(x)
    return arr


def permutation_sort(numbers: list, step: int):
    index = 0
    while not is_sorted(numbers):
        random.shuffle(numbers)
        index = index + 1
        if index == step:
            print(numbers)
            index = 0


def is_sorted(numbers: list) -> bool:
    for i in range(len(numbers)-1):
        if numbers[i] > numbers[i+1]:
            return False
    return True


def heap_sort(numbers: list, step: int):
    n = len(numbers)  # length of the array
    index = 0

    # Build a maxheap.
    for i in range(n // 2 - 1, -1, -1):
        max_heap(numbers, n, i)
        index = index + 1
        if index == step:
            print(numbers)
            index = 0

    # One by one extract elements
    for i in range(n - 1, 0, -1):
        aux = numbers[i]
        numbers[i] = numbers[0]
        numbers[0] = aux
        index = index + 1
        if index == step:
            print(numbers)
            index = 0
        max_heap(numbers, i, 0)
    pass


def max_heap(arr, N, i):
    largest = i  # Initialize largest as root
    left = 2 * i + 1
    right = 2 * i + 2

    # See if left child of root exists and is
    # greater than root
    if left < N and arr[largest] < arr[left]:
        largest = left

    # See if right child of root exists and is
    # greater than root
    if right < N and arr[largest] < arr[right]:
        largest = right

    # Change root, if needed
    if largest != i:
        aux = arr[i]
        arr[i] = arr[largest]
        arr[largest] = aux

        # Start from the root.
        max_heap(arr, N, largest)


def permutation_sort_np(numbers: list) -> float:
    """
    Sorts a list of numbers using permutation sort algorithm
    :param numbers: the list of numbers to be sorted
    :return: float: time it takes to sort in seconds
    """
    start = time.time()
    while not is_sorted(numbers):
        random.shuffle(numbers)
    end = time.time()
    return end - start


def heap_sort_np(numbers: list) -> float:
    """
    Sorts a list of numbers using heap sort algorithm
    :param numbers: the list of numbers to be sorted
    :return: float: time it takes to sort in seconds
    """

    start = time.time()
    n = len(numbers)  # length of the array

    # Build a maxheap.
    for i in range(n // 2 - 1, -1, -1):
        max_heap(numbers, n, i)

    # One by one extract elements
    for i in range(n - 1, 0, -1):
        aux = numbers[i]
        numbers[i] = numbers[0]
        numbers[0] = aux
        max_heap(numbers, i, 0)
    end = time.time()
    return end - start


def generate_lists() -> list[list[int]]:

    lengths = [3, 5, 8, 9, 10, 500, 1000, 2000, 4000, 8000]
    rand_numbers = []
    for i in range(0, 10):
        row = generate_numbers(lengths[i])
        rand_numbers.append(row)
    return rand_numbers


def arrange_best(arr: list[list[int]]):
    for i in range(0, 10):
        arr[i].sort()


def arrange_worst(arr: list[list[int]]):
    for i in range(0, 10):
        arr[i].sort(reverse=True)


sorting_message = "The program will show the list of numbers during the sorting process every x steps. How many steps do you want the program to make before showing progress?"
about_message = "This application helps visualize how sorting algorithms work."
print(about_message)
numbers = []
n = 0
while True:
    print("Please choose your option")
    print("1. Generate a list of random numbers between 0 and 100")
    print("2. Sort the numbers using permutation sort")
    print("3. Sort the numbers using heap sort")
    print("4. Best case sorting runtime")
    print("5. Worst case sorting runtime")
    print("6. Average case sorting runtime")
    print("7. Exit")

    option = int(input(">>> "))
    if option == 1:
        n = int(input("How many numbers do you want to generate?\n>>> "))
        numbers = generate_numbers(n)
        print(numbers)

    elif option == 2:
        if n == 0:
            print("Please generate a list of numbers before choosing a sorting option")
            continue
        else:
            print(sorting_message)
            steps = int(input(">>> "))
            permutation_sort(numbers, steps)
            print("Sorted list is: ")
            print(numbers)

    elif option == 3:
        if n == 0:
            print("Please generate a list of numbers before choosing a sorting option")
            continue
        else:
            print(sorting_message)
            steps = int(input(">>> "))
            heap_sort(numbers, steps)
            print("Sorted list is: ")
            print(numbers)

    elif option == 4:   # already sorted (only relevant for permutation sort)
        # best case
        best_list = generate_lists()
        arrange_best(best_list)
        print("The best case sorting runtime depending on length of the list is:")
        for i in range(0, 5):
            print("length: ", len(best_list[i]), "  |   ", "permutation sort time: ", permutation_sort_np(best_list[i]))
        for i in range(5, 10):
            print("length: ", len(best_list[i]), "  |   ", "heap sort time: ", heap_sort_np(best_list[i]))
        input("Press enter to continue...")

    elif option == 5:   # reverse order (irrelevant for either sort)
        # worst case
        worst_list = generate_lists()
        arrange_worst(worst_list)
        print("The worst case sorting runtime depending on length of the list is:")
        for i in range(0, 5):
            print("length: ", len(worst_list[i]), "  |   ", "permutation sort time: ", permutation_sort_np(worst_list[i]))
        for i in range(5, 10):
            print("length: ", len(worst_list[i]), "  |   ", "heap sort time: ", heap_sort_np(worst_list[i]))
        input("Press enter to continue...")

    elif option == 6:   # randomly generated
        # average case
        average_list = generate_lists()
        print("The average case sorting runtime depending on length of the list is:")
        for i in range(0, 5):
            print("length: ", len(average_list[i]), "  |   ", "permutation sort time: ", permutation_sort_np(average_list[i]))
        for i in range(5, 10):
            print("length: ", len(average_list[i]), "  |   ", "heap sort time: ", heap_sort_np(average_list[i]))
        input("Press enter to continue...")

    elif option == 7:   # exit
        break
    else:
        print("Please enter a valid option")
