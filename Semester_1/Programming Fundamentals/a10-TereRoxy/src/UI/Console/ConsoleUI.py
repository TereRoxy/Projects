class InvalidCommandError(Exception):
    """Exception raised when an invalid command is attempted.

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message


class ConsoleInterface:
    def __init__(self, service):
        self.__service = service

    def run(self):
        self.welcome_message()

        while True:
            self.print_boards()
            print("Enter command: ")
            command = input(">>> ")
            try:
                self.__parse_command(command)
            except Exception as e:
                print(e)

    @staticmethod
    def welcome_message():
        print("Welcome to Battleships!")
        print("You will play this game against the computer. Good luck!")
        print("Enter 'help' for a quick guide on how to play the game.")

    def __parse_command(self, command):
        if command == "help":
            self.help()

        elif command == "exit":
            exit()

        else:
            self.__parse_coordinates(command)

    @staticmethod
    def __check_command(command):
        if len(command) > 3:
            raise InvalidCommandError("Invalid command!")

        elif len(command) == 3:
            if command[1] != '1' or command[2] != '0':
                raise InvalidCommandError("Invalid command!")

        elif command[0] < 'A' or command[0] > 'J':
            raise InvalidCommandError("Invalid command!")

        elif len(command) == 2:
            if command[1] < '1' or command[1] > '9':
                raise InvalidCommandError("Invalid command!")

    def __parse_coordinates(self, command):
        try:
            self.__check_command(command)

            x = ord(command[0]) - ord('A')
            y = int(command[1]) - 1

            if len(command) == 3:
                y = 9

            ship = self.__service.player_move(x, y)
            if ship is None:
                print("You missed!")
            else:
                print("You hit a {}!".format(ship.Name()))
                if ship.sunk is True:
                    print("You sunk a {}!".format(ship.Name()))

            self.__service.computer_move()

            if self.__service.game_over():
                winner = self.__service.get_winner()
                self.__game_over(winner)

        except Exception as e:
            print(e)

    @staticmethod
    def help():
        print("This is a game of Battleships.")
        print("The game is played on a 10x10 grid.")
        print("Each player has 4 ships of different lengths: 2, 3, 4 and 5.")
        print("The ships are placed randomly on the board.")
        print("The players take turns to fire at the opponent's ships.")
        print("The first player to sink all the opponent's ships wins the game.")
        print("To fire at a ship, you must enter the coordinates of the cell you want to hit.")
        print("The coordinates must be entered in pairs of letters and numbers.")
        print("The letters must be between A and J and the numbers must be between 1 and 10 (e.g. A2).")
        print("The game ends when one player sinks all the opponent's ships.")
        print("Enter 'exit' to exit the game.")
        print("Enter your move in the following format: <letter><number> (e.g. A2).")
        # print("Enter 'start' to start a new game.")

    @staticmethod
    def __game_over(winner):
        print("Game over!")
        print("The winner is the " + winner + "!")
        exit()

    def print_boards(self):
        print("Your board:")
        print(self.__service.get_player_ship_board())
        print("Your hits:")
        print(self.__service.get_player_hit_board())
