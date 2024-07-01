# permutation sort
# heap sort

import random


def generate_numbers(n: int, arr: list):
    del arr[:]
    for i in range(0, n):
        x = random.randrange(0, 100)
        arr.append(x)


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
    print("4. Exit")
    option = int(input(">>> "))
    if option == 1:
        n = int(input("How many numbers do you want to generate?\n>>> "))
        generate_numbers(n, numbers)
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

    elif option == 4:
        break
    else:
        print("Please enter a valid option")