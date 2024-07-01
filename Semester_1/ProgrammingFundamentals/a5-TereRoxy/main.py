
def solve_problem_a(number_list):
    # parse the raw input into a list of complex numbers
    number_list = [parse_complex_number_input(number) for number in number_list]
    result = problem_a(number_list)
    # construct the output
    max_length = result[0]
    solution = result[1]
    print_solution_a(max_length, solution)


def problem_a(number_list) -> tuple:
    """
    Computes the length and elements of the longest subarray of numbers where their real part is in the form of a mountain
    :param number_list: array of complex numbers
    :return: max_length = maximum length, solution = the longest subarray
    The algorithm has time complexity O(n) and space complexity O(n) (for storing the longest subarray)
    """
    n = len(number_list)
    if n < 3:
        return 0, 0

    max_length = 0
    start_index = 0
    solution = []

    # iterate through the list
    while start_index < n - 2:
        # find the start of the first mountain (<=> while the real part is not increasing, go to the next number)
        # the start of the next mountain is updated each time we find the end of a mountain
        while start_index < n - 2 and get_real(number_list[start_index]) >= get_real(number_list[start_index + 1]):
            start_index += 1

        # find the peak of the mountain
        peak_index = start_index + 1
        while peak_index < n - 1 and get_real(number_list[peak_index]) < get_real(number_list[peak_index + 1]):
            peak_index += 1

        # find the end of the mountain
        end_index = peak_index + 1
        while end_index < n - 1 and get_real(number_list[end_index]) > get_real(number_list[end_index + 1]):
            end_index += 1

        # update the maximum
        if end_index - start_index + 1 > max_length:
            max_length = end_index - start_index + 1
            solution = number_list[start_index:end_index + 1]

        # move the starting pointer to the end of the mountain (=> O(n) complexity)
        start_index = end_index

    return max_length, solution


def print_solution_a(max_length: int, solution: list):
    # print the solution
    result = ""
    if max_length == 0:
        print("There is no mountain in the list!")
    else:
        print("The longest mountain has length " + str(max_length) + " and the numbers are: ")
        for i in range(0, len(solution)-1):
            result += unparsed_number_to_output(solution[i]) + ", "
        result += unparsed_number_to_output(solution[len(solution)-1])
    print(result)


def solve_problem_b(number_list):
    # parse the raw input into a list of complex numbers
    number_list = [parse_complex_number_input(number) for number in number_list]
    result = problem_b(number_list)
    # construct the output
    max_length = result[0]
    solution = result[1]
    solution.reverse()
    print_solution_b(max_length, solution)


def problem_b(number_list) -> tuple:
    """
    Computes the length and elements of the longest increasing subsequence, when considering each number's modulus
    :param number_list: array of complex numbers
    :return: max_length = maximum length, solution = the longest subarray
    The algorithm has time complexity O(n^2) and space complexity O(n) (for storing the longest subarray)
    """

    max_length = 0
    max_value = 0
    # construct the dynamic programming array
    dp = [1] * len(number_list)
    for i in range(0, len(number_list)):    # for each number in the list
        for j in range(0, i):      # we check all the numbers before it
            # we consider the longest subsequence ending in the current number (concat. it to the previous max length)
            if modulus(number_list[i]) > modulus(number_list[j]) and dp[i] < dp[j] + 1:
                dp[i] = dp[j] + 1
            # update the maximum length
            max_length = max(max_length, dp[i])

        max_value = max(max_value, modulus(number_list[i]))

    # construct the solution
    solution = []
    previous = max_value + 1
    current_length = max_length
    for i in range(len(number_list)-1, -1, -1):
        if dp[i] == current_length and modulus(number_list[i]) < previous:
            solution.append(number_list[i])
            current_length -= 1
            previous = modulus(number_list[i])

    return max_length, solution


def print_solution_b(max_length: int, solution: list):
    # print the solution
    result = ""
    if max_length == 0:
        print("There is no increasing subsequence in the list!")
    else:
        print("The longest increasing subsequence has length " + str(max_length) + " and the numbers are: ")
        for i in range(0, len(solution)-1):
            result += unparsed_number_to_output(solution[i]) + ", "
        result += unparsed_number_to_output(solution[len(solution)-1])
    print(result)


def modulus(number) -> float:
    real = get_real(number)
    imaginary = get_imaginary(number)
    return (real ** 2 + imaginary ** 2) ** 0.5


def create_complex_number(real: float, imaginary: float) -> list:
    return [real, imaginary]


def get_real(number: list) -> float:
    return number[0]


def get_imaginary(number: list) -> float:
    return number[1]
    

def set_real(number: list, real: float) -> list:
    number[0] = real
    return number
    

def set_imaginary(number: list, imaginary: float) -> list:
    number[1] = imaginary
    return number


# def create_complex_number(real: float, imaginary: float) -> dict:
#     return {"real": real, "imaginary": imaginary}
#
#
# def get_real(number: dict) -> float:
#     return number["real"]
#
#
# def get_imaginary(number: dict) -> float:
#     return number["imaginary"]
#
#
# def set_real(number: dict, real: float) -> dict:
#     number["real"] = real
#     return number
#
#
# def set_imaginary(number: dict, imaginary: float) -> dict:
#     number["imaginary"] = imaginary
#     return number


def show_menu():
    print("Complex numbers")
    print("1. Read a list of complex numbers")
    print("2. Print the list of numbers")
    print("3. Print the result of the required problem")
    print("4. Exit")


def show_submenu():
    print("Please choose the problem you want to see the solution to: ")
    print("a. Length and elements of a longest subarray of numbers where their real part is in the form of a mountain")
    print("   (first the values increase, then they decrease). (e.g. 1-i, 2+6i, 4-67i, 90+3i, 80-7i, 76+i, 43-12i, 3)")
    print("b. The length and elements of a longest increasing subsequence, when considering each number's modulus")


def get_option() -> int:
    op = int(input(">>> "))
    return op


def read_list() -> list:
    print("How many numbers do you want to enter?")
    n = int(input(">>> "))
    print("Please enter your numbers, each on a separate line: ")
    number_list = []
    for i in range(0, n):
        number = input(">>> ")
        number_list.append(number)
    return number_list


def print_list(numbers: list):
    string_numbers = ""
    for i in range(0, len(numbers)):
        string_numbers += str(numbers[i]) + " "
    print(string_numbers)


def unparsed_number_to_output(number) -> str:
    real = get_real(number)
    imaginary = get_imaginary(number)

    # round the real and imaginary parts if they are integers
    if real % 1 == 0:
        real = int(real)
    if imaginary % 1 == 0:
        imaginary = int(imaginary)

    # create the output string

    # if the number is real
    if imaginary == 0:
        return str(real)
    if real == 0:   # if the number has only imaginary part
        # implicit coefficient
        if imaginary == 1:
            return "i"
        if imaginary == -1:
            return "-i"
        return str(imaginary) + "i"     # explicit coefficient

    if imaginary == 1:
        return str(real) + "+i"
    if imaginary == -1:
        return str(real) + "-i"
    if imaginary > 0:
        return str(real) + "+" + str(imaginary) + "i"
    return str(real) + str(imaginary) + "i"


def parse_complex_number_input(number: str):
    """
    Parses a complex number from a given string
    :param number: represents a complex number in form a+bi with real quotients a and b
    :return: a and b parts in an object (either list or dictionary, depending on the implementation
    """
    number = number.strip()
    sign = 1.0
    i = 0

    # the number is real
    if 'i' not in number:
        real = float(number)
        imaginary = 0
        return create_complex_number(real, imaginary)

    # the number is imaginary and has implicit coefficient 1 or -1
    if number == 'i':
        real = 0.0
        imaginary = 1.0
        return create_complex_number(real, imaginary)
    if number == '-i':
        real = 0.0
        imaginary = -1.0
        return create_complex_number(real, imaginary)

    # the first part is negative
    if number[0] == '-':
        i = 1
        sign = -1.0

    first_part = ""
    while number[i] not in ['+', '-', 'i']:
        first_part = first_part + number[i]
        i += 1

    # the number has both real and imaginary parts
    if number[i] != 'i':
        real = sign * float(first_part)

        # reset sign
        if number[i] == '+':
            sign = 1.0
        else:
            sign = -1.0

        # the imaginary part has implicit coefficient 1 or -1
        if '+i' in number or '-i' in number:
            imaginary = sign
            return create_complex_number(real, imaginary)

        # the imaginary part has explicit coefficient
        second_part = ""
        i += 1
        while number[i] != 'i':
            second_part = second_part + number[i]
            i += 1
        imaginary = sign * float(second_part)

    # the number has only imaginary part
    else:
        real = 0.0
        imaginary = sign * float(first_part)

    return create_complex_number(real, imaginary)


def main_menu():
    show_menu()
    op = get_option()
    user_input_list = ["1-i", "2+6i", "4-67i", "90+3i", "80-7i", "76+i", "80-12i", "3", "i", "0"]
    while op != 4:
        if op == 1:
            user_input_list = read_list()
        elif op == 2:
            print_list(user_input_list)
        elif op == 3:
            show_submenu()
            sub_option = input(">>> ")
            if sub_option == 'a':
                solve_problem_a(user_input_list)
            elif sub_option == 'b':
                solve_problem_b(user_input_list)
            else:
                print("Invalid option!")
        else:
            print("Invalid option!")

        show_menu()
        op = get_option()


main_menu()
