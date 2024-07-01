#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here
#

import src.functions as f
from random import randint as r

invalid_command = "The command is invalid.\n"


def parse_complex_number_input(number: str):
    """
    Parses a complex number from a given string
    :param number: represents a complex number in form a+bi with real quotients a and b
    :return: a and b parts in an object (either list or dictionary, depending on the implementation
    Raises ValueError if the number is invalid
    """
    number = number.strip()
    sign = 1
    i = 0

    # the number is real
    if 'i' not in number:
        try:
            real = int(number)
            imaginary = 0
            return f.create_complex_number(real, imaginary)
        except ValueError:
            raise ValueError("The number is invalid.\n")

    # the first part is negative
    if number[0] == '-':
        i = 1
        sign = -1

    first_part = ""
    while number[i] not in ['+', '-', 'i']:
        first_part = first_part + number[i]
        i += 1

    # the number has both real and imaginary parts
    if number[i] != 'i':
        try:
            real = sign * int(first_part)
        except ValueError:
            raise ValueError("The number is invalid.\n")

        # reset sign
        if number[i] == '+':
            sign = 1
        else:
            sign = -1

        second_part = ""
        i += 1
        while number[i] != 'i':
            second_part = second_part + number[i]
            i += 1
        try:
            imaginary = sign * int(second_part)
        except ValueError:
            raise ValueError("The number is invalid.\n")

    # the number has only imaginary part
    else:
        real = 0
        imaginary = sign * float(first_part)

    return f.create_complex_number(real, imaginary)


def parse_command(command: str):
    command = command.strip()
    command = command.split(' ')
    return command


def select_command(command: str, numbers: list, history: list):
    new_list = numbers
    command = parse_command(command)
    if command[0] == 'add':
        history = f.update_history(history, new_list)
        new_list = execute_add(command, numbers)

    elif command[0] == 'insert':
        history = f.update_history(history, new_list)
        new_list = execute_insert(command, numbers)

    elif command[0] == 'remove':
        history = f.update_history(history, new_list)
        new_list = execute_remove(command, numbers)

    elif command[0] == 'replace':
        history = f.update_history(history, new_list)
        new_list = execute_replace(command, numbers)

    elif command[0] == 'list':
        numbers = execute_list(command, numbers)
        print_list(numbers)

    elif command[0] == 'filter':
        history = f.update_history(history, new_list)
        new_list = execute_filter(command, numbers)

    elif command[0] == 'undo':
        new_list, history = execute_undo(command, numbers, history)
    else:
        print(invalid_command)
    return new_list, history


def execute_add(command, numbers) -> list:
    if len(command) != 2:
        print(invalid_command)
    else:
        try:
            number = parse_complex_number_input(command[1])
            result = f.add_to_list(numbers, number)
            return result
        except ValueError as err:
            print(str(err) + invalid_command)
    return numbers


def execute_insert(command, numbers) -> list:

    if len(command) != 4 or command[2] != 'at':
        print(invalid_command)
    else:
        try:
            number = parse_complex_number_input(command[1])
            position = int(command[3])
            result = f.insert_number_position(numbers, number, position)
            return result
        except ValueError or IndexError as err:
            print(str(err) + invalid_command)
    return numbers


def execute_remove(command, numbers) -> list:

    if len(command) == 2:
        try:
            position = int(command[1])
            result = f.remove_position(numbers, position)
            return result
        except ValueError or IndexError as err:
            print(str(err) + invalid_command)

    elif len(command) == 4 and command[2] == 'to':
        try:
            start_position = int(command[1])
            end_position = int(command[3])
            result = f.remove_range(numbers, start_position, end_position)
            return result
        except ValueError or IndexError as err:  # the positions are not integers
            print(str(err) + invalid_command)
    else:
        print(invalid_command)
    return numbers


def execute_replace(command, numbers) -> list:

    if len(command) != 4 or command[2] != 'with':
        print(invalid_command)
    else:
        try:
            old_number = parse_complex_number_input(command[1])
            new_number = parse_complex_number_input(command[3])
            result = f.replace_number(numbers, old_number, new_number)
            return result
        except ValueError:
            print(ValueError)
            return numbers


def execute_list(command, numbers) -> list:
    if len(command) == 1:
        result = numbers
        return result
    elif command[1] == 'real' and len(command) == 5 and command[3] == 'to':
        try:
            start_position = int(command[2])
            end_position = int(command[4])
            result = f.list_real_numbers(numbers, start_position, end_position)
            return result
        except ValueError as err:   # the positions are not integers
            print(str(err) + invalid_command)

    elif command[1] == 'modulo' and len(command) == 4:
        try:
            sign = command[2]
            number = float(command[3])
            result = f.filter_modulus(numbers, sign, number)
            return result
        except ValueError as err:   # the number is not a float
            print(str(err) + invalid_command)
    else:
        print(invalid_command)
    return numbers


def execute_filter(command, numbers) -> list:

    if len(command) == 2 and command[1] == 'real':
        result = f.filter_real_numbers(numbers)
        return result
    elif len(command) == 4:
        try:
            sign = command[2]
            number = float(command[3])
            result = f.filter_modulus(numbers, sign, number)
            return result
        except ValueError as err:
            print(str(err) + invalid_command)
    else:
        print(invalid_command)
    return numbers


def execute_undo(command, numbers, history):
    if len(command) != 1:
        print(invalid_command)
    try:
        result, history = f.undo(history)
        return result, history
    except ValueError as err:
        print(str(err) + invalid_command)
        return numbers, numbers


def provide_starting_list():
    numbers = []

    for i in range(10):
        real = r(-10, 10)
        imaginary = r(-10, 10)
        numbers.append(f.create_complex_number(real, imaginary))

    return numbers


def print_list(numbers: list):
    string = ''
    for i in range(len(numbers)-1):
        string += unparsed_number_to_string(numbers[i]) + ', '
    string += unparsed_number_to_string(numbers[len(numbers)-1])
    print(string)


def unparsed_number_to_string(number: list) -> str:
    """
    Converts a complex number from a list to a string
    :param number: the complex number
    :return: the string
    """
    if f.get_imaginary(number) == 0:
        return str(f.get_real(number))
    elif f.get_real(number) == 0:
        return str(f.get_imaginary(number)) + 'i'
    elif f.get_imaginary(number) > 0:
        return str(f.get_real(number)) + '+' + str(f.get_imaginary(number)) + 'i'
    else:
        return str(f.get_real(number)) + str(f.get_imaginary(number)) + 'i'


def print_menu():
    print("Welcome! Please type one of the following commands:")
    print("A. Add a number")
    print("add <number>")
    print("insert <number> at <position>")
    print()
    print("B. Modify numbers")
    print("remove <position>")
    print("remove <start position> to <end position>")
    print("replace <old number> with <new number>")
    print()
    print("C. Display numbers having different properties")
    print("list")
    print("list real <start position> to <end position>")
    print("list modulo [ < | = | > ] <number>")
    print()
    print("D. Filter list")
    print("filter real")
    print("filter modulo [ < | = | > ] <number>")
    print()
    print("E. Undo")
    print("undo")
    print()
    print("F. Exit")
    print("exit")
