#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#

import src.ui as ui
import src.functions as f


def start():
    numbers = ui.provide_starting_list()
    history = []
    ui.print_menu()
    while True:
        print("Enter command: ")
        command = input(">>> ")
        if command == 'exit':
            return
        numbers, history = ui.select_command(command, numbers, history)


def test_start():
    f.test_add_to_list()
    f.test_insert_number_position()
    f.test_remove_position()
    f.test_replace_number()
    f.test_remove_range()


test_start()
start()

