import random


class ComputerMove:
    def __init__(self, strategy=None):
        """
        This class is used to generate a computer move. If no strategy is given,
        the computer will generate a random move.
        """
        self.__x = random.randint(0, 9)
        self.__y = random.randint(0, 9)
        self.__strategy = strategy

        if self.__strategy is not None:
            self.__make_move()

    def get_move(self):
        """
        This method is used to get the computer move.
        :return: the coordinates of the computer move
        """
        return self.__x, self.__y

    # TODO: implement this method
    def __make_move(self):
        pass
