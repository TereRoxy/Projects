class Board:
    def __init__(self):
        self.content = []
        self.size = 10
        self.__create_board()

    def __eq__(self, other):
        if isinstance(other, Board):
            return ((self.content == other.content) and (self.size == other.size))
        return False

    def __str__(self):
        print_result = ""
        for i in range(self.size):
            for j in range(self.size):
                print_result += str(self.content[i][j]) + " "
            print_result += "\n"
        return print_result

    def __create_board(self):
        for i in range(self.size):
            self.content.append([])
            for j in range(self.size):
                self.content[i].append(0)
