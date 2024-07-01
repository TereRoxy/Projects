import unittest

from src.Assets.board import Board
from src.Assets.ships import *
from src.Assets.player_assets import ShipBoard, HitBoard


class BoardInitTest(unittest.TestCase):
    def test_init(self):
        board1 = Board()
        board2 = Board()
        self.assertEqual(board1.content, board2.content)  # add assertion here

    def test_size(self):
        board = Board()
        self.assertEqual(board.size, 10)


class ShipsTest(unittest.TestCase):
    def test_carrier(self):
        ship = Carrier()
        self.assertEqual(5, ship.Length())
        self.assertEqual("Carrier", ship.Name())

    def test_battleship(self):
        ship = Battleship()
        self.assertEqual(4, ship.Length())
        self.assertEqual("Battleship", ship.Name())

    def test_cruiser(self):
        ship = Cruiser()
        self.assertEqual(3, ship.Length())
        self.assertEqual("Cruiser", ship.Name())

    def test_destroyer(self):
        ship = Destroyer()
        self.assertEqual(2, ship.Length())
        self.assertEqual("Destroyer", ship.Name())


class PlayerShipBoardTest(unittest.TestCase):
    def test_init(self):
        board = Board()
        ship = Carrier()
        ship_board = ShipBoard(board, [ship])
        self.assertEqual(ship_board.get_ship_layer(), board)
        self.assertEqual(ship_board.get_hit_layer(), board)
        self.assertEqual(ship_board.get_ships(), [ship])

    def test_take_hit(self):
        # manually place a ship on the board
        board = Board()
        ship = Carrier()
        ship.cells = [[0, 0], [1, 0], [2, 0], [3, 0], [4, 0]]
        for i in range(5):
            board.content[0][i] = 5
        ship_board = ShipBoard(board, [ship])

        # test a hit to the ship
        ship_board.take_hit(0, 0)
        self.assertEqual(ship_board.get_ship_layer().content[0][0], 5)
        self.assertEqual(ship_board.get_hit_layer().content[0][0], 1)
        self.assertEqual(ship.hits, 1)
        self.assertEqual(ship.sunk, False)

        # test a miss
        ship_board.take_hit(0, 1)
        self.assertEqual(ship_board.get_ship_layer().content[1][0], 0)
        self.assertEqual(ship_board.get_hit_layer().content[1][0], -1)

    def test_update_ship(self):
        board = Board()
        ship = Carrier()
        ship.cells = [[0, 0], [1, 0], [2, 0], [3, 0], [4, 0]]
        for i in range(5):
            board.content[0][i] = 5
        ship_board = ShipBoard(board, [ship])
        ship_board.take_hit(0, 0)
        ship_board.take_hit(1, 0)
        ship_board.take_hit(2, 0)
        ship_board.take_hit(3, 0)
        ship_board.take_hit(4, 0)
        self.assertEqual(ship.sunk, True)

    def test_all_sunk(self):
        board = Board()
        ship1 = Carrier()
        ship2 = Battleship()
        ship3 = Cruiser()
        ship4 = Destroyer()
        ship5 = Destroyer()
        ship1.cells = [[0, 0], [1, 0], [2, 0], [3, 0], [4, 0]]
        ship2.cells = [[0, 1], [1, 1], [2, 1], [3, 1]]
        ship3.cells = [[0, 2], [1, 2], [2, 2]]
        ship4.cells = [[0, 3], [1, 3]]
        ship5.cells = [[0, 4], [1, 4]]
        for i in range(5):
            board.content[0][i] = 5
        for i in range(4):
            board.content[1][i] = 4
        for i in range(3):
            board.content[2][i] = 3
        for i in range(2):
            board.content[3][i] = 2
        for i in range(2):
            board.content[4][i] = 2
        ship_board = ShipBoard(board, [ship1, ship2, ship3, ship4, ship5])
        self.assertEqual(ship_board.all_sunk(), False)
        ship_board.take_hit(0, 0)
        ship_board.take_hit(1, 0)
        ship_board.take_hit(2, 0)
        ship_board.take_hit(3, 0)
        ship_board.take_hit(4, 0)
        ship_board.take_hit(0, 1)
        ship_board.take_hit(1, 1)
        ship_board.take_hit(2, 1)
        ship_board.take_hit(3, 1)
        ship_board.take_hit(0, 2)
        ship_board.take_hit(1, 2)
        ship_board.take_hit(2, 2)
        ship_board.take_hit(0, 3)
        ship_board.take_hit(1, 3)
        ship_board.take_hit(0, 4)
        ship_board.take_hit(1, 4)
        self.assertEqual(ship_board.all_sunk(), True)


class HitBoardTest(unittest.TestCase):
    def test_init(self):
        board = Board()
        hit_board = HitBoard()
        self.assertEqual(hit_board.get_hit_layer(), board)

    def test_mark_hit(self):
        board = Board()
        hit_board = HitBoard()
        hit_board.mark_hit(0, 0, 1)
        self.assertEqual(hit_board.get_hit_layer().content[0][0], 1)
        hit_board.mark_hit(0, 0, -1)
        self.assertEqual(hit_board.get_hit_layer().content[0][0], -1)
        hit_board.mark_hit(0, 0, 0)
        self.assertEqual(hit_board.get_hit_layer().content[0][0], 0)

    def test_check_hit(self):
        hit_board = HitBoard()
        hit_board.mark_hit(0, 0, 1)
        self.assertEqual(hit_board.check_hit(0, 0), True)
        self.assertEqual(hit_board.check_hit(1, 1), False)


if __name__ == '__main__':
    unittest.main()
