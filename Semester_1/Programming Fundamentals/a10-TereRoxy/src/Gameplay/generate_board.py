from src.Assets.board import Board
from src.Assets.ships import *
import random as rnd


class PlaceShips:
    def __init__(self):
        """
        This class is used to generate a board with ships placed randomly.
        __ships_placement is a Board object that contains the ships placed randomly.
        __ships is a list of lists that contains the number of ships and the ship objects that need to be placed.
        """
        self.__board = Board()
        self.__ship_descriptors = [[1, "Carrier"], [2, "Battleship"], [3, "Cruiser"], [4, "Destroyer"]]
        self.__ships = []
        self.__create_ships()
        self.__place_ships()

    def __create_ships(self):
        """
        This method creates the ship objects that need to be placed.
        :return:
        """
        for number, ship_type in self.__ship_descriptors:
            for i in range(number):
                if ship_type == "Carrier":
                    new_ship = Carrier()
                elif ship_type == "Battleship":
                    new_ship = Battleship()
                elif ship_type == "Cruiser":
                    new_ship = Cruiser()
                else:
                    new_ship = Destroyer()

                self.__ships.append(new_ship)

    def __place_ships(self):
        """
        This method places all the ships on the board.
        :return:
        """
        for ship in self.__ships:
            self.__place_ship(ship)

    def __place_ship(self, ship):
        """
        This method places a ship randomly on the board.
        :param ship: the ship that needs to be placed
        :return:
        The method ensures that the ship is placed in a valid position.
        A position is valid if the ship does not overlap with another ship, and it fits on the board.
        """
        placed = False
        occupied_cells = []
        while not placed:
            direction = rnd.randint(0, 1)

            if direction == 0:  # horizontal placement
                x = rnd.randint(0, 9 - ship.Length())   # the ship must fit on the board
                y = rnd.randint(0, 9)

                if self.__check_horizontal(ship, x, y):
                    occupied_cells = self.__place_horizontal(ship, x, y)
                    placed = True
            else:            # vertical placement
                x = rnd.randint(0, 9)
                y = rnd.randint(0, 9 - ship.Length())  # the ship must fit on the board

                if self.__check_vertical(ship, x, y):
                    occupied_cells = self.__place_vertical(ship, x, y)
                    placed = True

        ship.cells = occupied_cells

    def __check_horizontal(self, ship, x, y):
        """
        This method checks if a ship can be placed horizontally on the board.
        A ship can be placed horizontally if it does not overlap with another ship in its corresponding row.
        :param ship: the ship that needs to be placed
        :param x: the starting column coordinate (the leftmost cell)
        :param y: the row coordinate
        :return: True if the position is valid, False otherwise.
        """
        for i in range(ship.Length()):
            if self.__board.content[y][x + i] != 0:
                return False
        return True

    def __place_horizontal(self, ship, x, y):
        """
        This method places a ship horizontally on the board.
        It updates the contents of the __board attribute of the class.
        :param ship: the ship that needs to be placed
        :param x: the starting column coordinate (the leftmost cell)
        :param y: the row coordinate
        :return: the list of coordinates of the cells that the ship occupies
        """
        occupied_cells = []
        for i in range(ship.Length()):
            self.__board.content[y][x + i] = ship.Length()
            occupied_cells.append([x + i, y])
        return occupied_cells

    def __check_vertical(self, ship, x, y):
        """
        This method checks if a ship can be placed vertically on the board.
        A ship can be placed vertically if it does not overlap with another ship in its corresponding column.
        :param ship: the ship that needs to be placed
        :param x: the column coordinate
        :param y: the starting row coordinate (the topmost cell)
        :return: True if the position is valid, False otherwise.
        """
        for i in range(ship.Length()):
            if self.__board.content[y + i][x] != 0:
                return False
        return True

    def __place_vertical(self, ship, x, y):
        """
        This method places a ship vertically on the board.
        It updates the contents of the __board attribute of the class.
        :param ship: the ship that needs to be placed
        :param x: the column coordinate
        :param y: the starting row coordinate (the topmost cell)
        :return: the list of coordinates of the cells that the ship occupies
        """
        occupied_cells = []
        for i in range(ship.Length()):
            self.__board.content[y + i][x] = ship.Length()
            occupied_cells.append([x, y + i])
        return occupied_cells

    def get_ships_placement(self):
        return self.__board

    def get_ships(self):
        return self.__ships
