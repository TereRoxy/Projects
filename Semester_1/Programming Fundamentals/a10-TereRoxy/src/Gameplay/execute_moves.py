from src.Gameplay.computer_strategy import ComputerMove


class InvalidMoveError(Exception):
    """Exception raised when an invalid move is attempted.

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message


class BoardsContainer:
    def __init__(self, player_ship_board, player_hit_board, computer_ship_board, computer_hit_board):
        """
        This class is used to store the boards of the player and the computer.
        :param player_ship_board: the player ship board
        :param player_hit_board: the player hit board
        :param computer_ship_board: the computer ship board
        :param computer_hit_board: the computer hit board
        """
        self.player_ship_board = player_ship_board
        self.player_hit_board = player_hit_board
        self.computer_ship_board = computer_ship_board
        self.computer_hit_board = computer_hit_board


class ExecuteMoves:
    def __init__(self, boards, computer_strategy):
        """
        This class is used to execute the moves of the player and the computer.
        :param boards: the container object used to store all the boards
        """
        self.__player_ship_board = boards.player_ship_board
        self.__player_hit_board = boards.player_hit_board
        self.__computer_ship_board = boards.computer_ship_board
        self.__computer_hit_board = boards.computer_hit_board
        self.__computer_strategy = computer_strategy

    def get_player_ship_board(self):
        """
        This method is used to get the player ship board.
        :return: the player ship board
        """
        return self.__player_ship_board

    def get_player_hit_board(self):
        """
        This method is used to get the player hit board.
        :return: the player hit board
        """
        return self.__player_hit_board

    def get_computer_ship_board(self):
        """
        This method is used to get the computer ship board.
        :return: the computer ship board
        """
        return self.__computer_ship_board

    def get_computer_hit_board(self):
        """
        This method is used to get the computer hit board.
        :return: the computer hit board
        """
        return self.__computer_hit_board

    def player_move(self, x, y):
        """
        This method is used to execute the player move.
        :param x: the column coordinate of the move
        :param y: the row coordinate of the move
        :return: the type of the ship that was hit or None if no ship was hit
        """
        if x < 0 or x > 9 or y < 0 or y > 9:
            raise InvalidMoveError("Invalid coordinates!")
        if self.__player_hit_board.check_hit(x, y):
            raise InvalidMoveError("You already hit this cell!")
        else:
            ship = self.__computer_ship_board.take_hit(x, y)
            if ship is None:
                hit_value = -1
            elif ship.sunk is False:
                hit_value = 1
            else:   # ship.sunk is True
                hit_value = 2
                for cell in ship.cells:
                    x = cell[0]
                    y = cell[1]
                    self.__player_hit_board.mark_hit(x, y, hit_value)

            self.__player_hit_board.mark_hit(x, y, hit_value)
            return ship

    def computer_move(self):
        """
        This method is used to execute the computer move.
        :return: the type of the ship that was hit or None if no ship was hit
        """
        comp_move = ComputerMove(self.__computer_strategy)
        x, y = comp_move.get_move()
        if self.__computer_hit_board.check_hit(x, y):
            return self.computer_move()
        else:
            ship = self.__player_ship_board.take_hit(x, y)
            if ship is None:
                hit_value = -1
            elif ship.sunk is False:
                hit_value = 1
            else:   # ship.sunk is True
                hit_value = 2
                for cell in ship.cells:
                    x = cell[0]
                    y = cell[1]
                    self.__computer_hit_board.mark_hit(x, y, hit_value)

            self.__computer_hit_board.mark_hit(x, y, hit_value)
            return ship

    def game_over(self):
        """
        This method is used to check if the game is over.
        :return: True if the game is over, False otherwise
        """
        if self.__player_ship_board.all_sunk() or self.__computer_ship_board.all_sunk():
            return True
        else:
            return False

    def get_winner(self):
        """
        This method is used to get the winner of the game.
        :return: the winner of the game
        """
        if self.__computer_ship_board.all_sunk():
            return "Player"
        else:
            return "Computer"
