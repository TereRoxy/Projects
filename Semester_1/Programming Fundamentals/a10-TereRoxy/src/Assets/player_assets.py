from src.Assets.board import Board


class ShipBoard:
    def __init__(self, generated_board, ships):
        """
        This class is used to store the player's ship board.
        The ship_layer is a Board object that contains the ships placed randomly.
        The hit_layer is a Board object that contains the hits that the computer made against the player.
        :param generated_board: the board with the encodings of the ships placed randomly
        ship_layer.content[i][j] = 0 if the cell is empty, <ship_id> if the cell has a ship (number from 1 to 5)
        hit_layer.content[i][j] = 0 if the cell was not hit, 1 if the hit was successful, -1 if the hit was a miss
        """
        self.__ship_layer = generated_board
        self.__ships = ships
        self.__hit_layer = Board()

    def get_ships(self):
        """
        This method is used to get the ships that are placed on the board.
        :return: the ships that are placed on the board
        """
        return self.__ships

    def get_ship_layer(self):
        """
        This method is used to get the ship layer of the board.
        :return: the ship layer of the board
        """
        return self.__ship_layer

    def get_hit_layer(self):
        """
        This method is used to get the hit layer of the board.
        :return: the hit layer of the board
        """
        return self.__hit_layer

    def __str__(self):
        """
        This method is used to format for print the ship board.
        :return: A string ready to be printed
        """
        print_result = "    A B C D E F G H I J\n"
        for i in range(10):
            if i != 9:
                print_result += " {}  ".format(i + 1)
            else:
                print_result += "{}  ".format(i + 1)
            for j in range(10):
                # if the cell is empty and it was not hit
                if self.__ship_layer.content[i][j] == 0 and self.__hit_layer.content[i][j] == 0:
                    print_result += ". "
                # if the cell has a ship and it was hit
                elif self.__hit_layer.content[i][j] == 1:
                    print_result += "O "
                # if the cell is empty and it was hit
                elif self.__hit_layer.content[i][j] == -1:
                    print_result += "X "
                # if the cell has a ship and it was not hit
                else:
                    print_result += "- "
            print_result += "\n"
        return print_result

    def take_hit(self, column, row):
        """
        This method is used to take a hit on the ship board.
        :param column: the column coordinate of the hit
        :param row: the row coordinate of the hit
        :return: the type of the ship that was hit or None if no ship was hit
        """
        if self.__ship_layer.content[row][column] == 0:
            self.__hit_layer.content[row][column] = -1
            return None
        else:
            self.__hit_layer.content[row][column] = 1
            # print(self.__hit_layer)
            ship = self.get_ship_by_coordinate(column, row)
            if ship is not None:
                self.update_ship(ship)
            return ship

    @staticmethod
    def update_ship(ship):
        """
        This method is used to update a ship attributes after it was hit.
        :param ship:
        :return:
        """
        ship.hits += 1
        if ship.hits == ship.Length():
            ship.sunk = True

    def get_ship_by_coordinate(self, column, row):
        """
        This method is used to get the ship that occupies the cell with the given coordinates.
        :param column: the column coordinate of the cell
        :param row: the row coordinate of the cell
        :return: the ship that occupies the cell with the given coordinates
        """
        for ship in self.__ships:
            if [column, row] in ship.cells:
                return ship

    def all_sunk(self):
        """
        This method is used to check if all the ships on the board are sunk.
        :return: True if all the ships are sunk, False otherwise
        """
        for ship in self.__ships:
            if ship.sunk is False:
                return False
        return True


class HitBoard:
    def __init__(self):
        """
        This class is used to store the player's hit board (the board that shows the hits against the opponent).
        hit_layer.content[i][j] = 0 if the cell was not hit, 1 if the hit was successful, 2 if the ship has been sunk,
                                    -1 if the hit was a miss
        """
        self.__hit_layer = Board()

    def get_hit_layer(self):
        """
        This method is used to get the hit layer of the board.
        :return: the hit layer of the board
        """
        return self.__hit_layer

    def __str__(self):
        print_result = "    A B C D E F G H I J\n"
        for i in range(10):
            if i != 9:
                print_result += " {}  ".format(i + 1)
            else:
                print_result += "{}  ".format(i + 1)
            for j in range(10):
                # if the cell is empty and it was not hit
                if self.__hit_layer.content[i][j] == 0:
                    print_result += ". "
                # if the cell has a ship that was hit, but not sunk
                elif self.__hit_layer.content[i][j] == 1:
                    print_result += "O "
                # if the cell has a ship that was hit and sunk
                elif self.__hit_layer.content[i][j] == 2:
                    print_result += "# "
                # if the cell is empty and it was hit
                elif self.__hit_layer.content[i][j] == -1:
                    print_result += "X "
            print_result += "\n"
        return print_result

    def check_hit(self, column, row):
        """
        This method is used to check if a hit was made on the hit board.
        :param column: the column coordinate of the hit
        :param row: the row coordinate of the hit
        :return: True if the hit was made, False otherwise
        """
        if self.__hit_layer.content[row][column] == 0:
            return False
        else:
            return True

    def mark_hit(self, column, row, value):
        """
        This method is used to mark a hit on the hit board.
        :param column: the column coordinate of the hit
        :param row: the row coordinate of the hit
        :param value: the value that will be assigned to the cell
        :return:
        Value -1 means that the hit was unsuccessful. Value 1 means that the hit was successful.
        Value 2 means that the hit was successful and the ship was sunk.
        """
        self.__hit_layer.content[row][column] = value
