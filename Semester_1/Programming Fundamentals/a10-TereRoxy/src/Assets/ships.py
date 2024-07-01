class Ship:
    def __init__(self, name, length, symbol):
        """
        This class is used to create a ship object.
        __name is the name of the ship.
        __length is the length of the ship.
        __symbol is the symbol that represents the ship on the board.
        hits is the number of hits that the ship has taken.
        cells is a list of tuples that contains the coordinates of the cells that the ship occupies
                in (column, row) format.
        """
        self.__name = name
        self.__length = length
        self.__symbol = symbol
        self.hits = 0
        self.cells = []
        self.sunk = False

    def Name(self):
        return self.__name

    def Length(self):
        return self.__length

    def Symbol(self):
        return self.__symbol


class Carrier(Ship):
    def __init__(self):
        super().__init__("Carrier", 5, "C")


class Battleship(Ship):
    def __init__(self):
        super().__init__("Battleship", 4, "B")


class Cruiser(Ship):
    def __init__(self):
        super().__init__("Cruiser", 3, "R")


class Destroyer(Ship):
    def __init__(self):
        super().__init__("Destroyer", 2, "D")
