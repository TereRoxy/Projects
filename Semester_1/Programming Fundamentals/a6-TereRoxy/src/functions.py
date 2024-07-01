#
# The program's functions are implemented here. There is no user interaction in this file,
# therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
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


def modulus(number) -> float:
    """
    This function computes and returns the absolute value of a complex number
    :param number: the number to be processed
    :return: the absolute value
    """
    real = get_real(number)
    imaginary = get_imaginary(number)
    return (real ** 2 + imaginary ** 2) ** 0.5


def add_to_list(numbers: list, element) -> list:
    """
    Appends an element to the end of the list of complex numbers
    :param numbers: list of complex numbers
    :param element: the element to be added
    :return: Returns the modified list
    """
    numbers.append(element)
    return numbers


def insert_number_position(numbers: list, element, position: int) -> list:
    """
    Inserts an element at position x in the list of complex numbers
    :param numbers: the list
    :param element: number to be inserted
    :param position: the index where the element is inserted
    :return: Returns the modified list
    Raises exception if IndexOutRange is encountered
    """
    if position > len(numbers) or position < 0:
        raise IndexError("This index is out of range.\n")
    elif position == len(numbers):
        numbers.append(element)
    else:
        numbers.insert(position, element)

    return numbers


def replace_number(numbers: list, old_number, new_number) -> list:
    """
    Replaces all occurrences of an element in the list with another element
    :param numbers: the list of numbers
    :param old_number: the element to be replaced
    :param new_number: the element to replace with
    :return: Returns the modified list
    Raises exception if the old number is not found in the list
    """
    if old_number not in numbers:
        raise ValueError("The old number is not in the list.\n")
    else:
        for i in range(len(numbers)):
            if numbers[i] == old_number:
                numbers[i] = new_number
    return numbers


def remove_position(numbers: list, position: int) -> list:
    """
    Removes the element at position x in the list of complex numbers
    :param numbers: the list of numbers
    :param position: the index where the element is removed
    :return: Returns the modified list
    Raises exception if IndexOutRange is encountered
    """
    if position < 0 or position > len(numbers):
        raise IndexError("The given position is out of bounds.\n")
    else:
        del numbers[position]
    return numbers


def remove_range(numbers: list, start: int, end: int) -> list:
    """
    Removes all elements between start and end
    :param numbers: the list of elements
    :param start: start index
    :param end: end index
    :return: the modified list
    Raises exception if IndexOutRange is encountered or if start > end
    """
    if start < 0 or end > len(numbers):
        raise IndexError("The given range is out of bounds.\n")
    elif start > end:
        raise ValueError("The start index cannot be greater than the end index.\n")
    else:
        del numbers[start:end+1]
    return numbers


def list_real_numbers(numbers: list, start: int, end: int) -> list:
    """
    Returns the list of real numbers between start and end
    :param numbers: the list
    :param start: start index
    :param end: end index
    :return: the list of real numbers
    Raises exception if IndexOutRange is encountered or if start > end
    """
    if start < 0 or end > len(numbers):
        raise IndexError("The given range is out of bounds.\n")
    elif start > end:
        raise ValueError("The start index cannot be greater than the end index.\n")
    else:
        real_numbers = []
        for i in range(start, end+1):
            if get_imaginary(numbers[i]) == 0:
                real_numbers.append(numbers[i])
    return real_numbers


def filter_modulus(numbers: list, sign: str, number: float) -> list:
    """
    Returns the list of numbers having the modulus <, = or > than a given number
    :param numbers: the list
    :param sign: the sign of the modulus
    :param number: the number to be compared to
    :return: the list of numbers
    Raises exception if the sign is not <, = or >
    """
    if sign not in ['<', '=', '>']:
        raise ValueError("The sign is invalid.\n")
    else:
        modulus_numbers = []
        for i in range(len(numbers)):
            if sign == '<':
                if modulus(numbers[i]) < number:
                    modulus_numbers.append(numbers[i])
            elif sign == '=':
                if modulus(numbers[i]) == number:
                    modulus_numbers.append(numbers[i])
            elif sign == '>':
                if modulus(numbers[i]) > number:
                    modulus_numbers.append(numbers[i])
    return modulus_numbers


def filter_real_numbers(numbers: list) -> list:
    """
    Returns the list of real numbers
    :param numbers: the list to be filtered
    :return: the list of real numbers
    """
    real_numbers = []
    for i in range(len(numbers)):
        if get_imaginary(numbers[i]) == 0:
            real_numbers.append(numbers[i])
    return real_numbers


def update_history(history: list, numbers: list) -> list:
    """
    Adds a new list of numbers to the history
    :param history: the list of lists
    :param numbers: the list of numbers to be added
    :return: the modified history
    """
    numbers_copy = []
    for i in range(len(numbers)):
        numbers_copy.append(numbers[i])
    history.append(numbers_copy)
    return history


def undo(history: list):
    """
    Undoes the last operation
    :param history: the list of data before the last operation
    :return: values before the last operation
    Raises exception if the history is empty (no more undoes available)
    """
    if len(history) == 0:
        raise ValueError("No more undoes available.\n")
    else:
        last_operation = history.pop()
        return last_operation, history


def test_add_to_list():
    numbers = []
    numbers = add_to_list(numbers, create_complex_number(1, 2))
    assert len(numbers) == 1
    assert numbers[0] == [1, 2]
    numbers = add_to_list(numbers, create_complex_number(3, 4))
    assert len(numbers) == 2
    assert numbers[1] == [3, 4]


def test_insert_number_position():
    numbers = []
    numbers = insert_number_position(numbers, create_complex_number(1, 2), 0)
    assert len(numbers) == 1
    assert numbers[0] == [1, 2]
    numbers = insert_number_position(numbers, create_complex_number(3, 4), 1)
    assert len(numbers) == 2
    assert numbers[1] == [3, 4]
    numbers = insert_number_position(numbers, create_complex_number(5, 6), 1)
    assert len(numbers) == 3
    assert numbers[1] == [5, 6]
    try:
        numbers = insert_number_position(numbers, create_complex_number(7, 8), 4)
        assert False
    except IndexError:
        assert True
    try:
        numbers = insert_number_position(numbers, create_complex_number(7, 8), -1)
        assert False
    except IndexError:
        assert True


def test_replace_number():
    numbers = []
    numbers = add_to_list(numbers, create_complex_number(1, 2))
    numbers = add_to_list(numbers, create_complex_number(3, 4))
    numbers = add_to_list(numbers, create_complex_number(5, 6))
    numbers = add_to_list(numbers, create_complex_number(7, 8))
    numbers = replace_number(numbers, create_complex_number(3, 4), create_complex_number(9, 10))
    assert numbers[1] == [9, 10]
    try:
        numbers = replace_number(numbers, create_complex_number(11, 12), create_complex_number(13, 14))
        assert False
    except ValueError:
        assert True


def test_remove_position():
    numbers = []
    numbers = add_to_list(numbers, create_complex_number(1, 2))
    numbers = add_to_list(numbers, create_complex_number(3, 4))
    numbers = add_to_list(numbers, create_complex_number(5, 6))
    numbers = add_to_list(numbers, create_complex_number(7, 8))
    numbers = remove_position(numbers, 2)
    assert len(numbers) == 3
    assert numbers[2] == [7, 8]
    try:
        numbers = remove_position(numbers, 4)
        assert False
    except IndexError:
        assert True
    try:
        numbers = remove_position(numbers, -1)
        assert False
    except IndexError:
        assert True


def test_remove_range():
    numbers = []
    numbers = add_to_list(numbers, create_complex_number(1, 2))
    numbers = add_to_list(numbers, create_complex_number(3, 4))
    numbers = add_to_list(numbers, create_complex_number(5, 6))
    numbers = add_to_list(numbers, create_complex_number(7, 8))
    numbers = remove_range(numbers, 1, 2)
    assert len(numbers) == 2
    assert numbers[1] == [7, 8]
    try:
        numbers = remove_range(numbers, 2, 1)
        assert False
    except ValueError:
        assert True
    try:
        numbers = remove_range(numbers, 4, 5)
        assert False
    except IndexError:
        assert True
    try:
        numbers = remove_range(numbers, -1, 2)
        assert False
    except IndexError:
        assert True
