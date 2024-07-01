import unittest
from src.Gameplay.execute_moves import ExecuteMoves
from src.Gameplay.generate_board import PlaceShips
from src.Assets.player_assets import ShipBoard, HitBoard
from src.Gameplay.execute_moves import BoardsContainer


class PlaceShipsTest(unittest.TestCase):
    def test_place_ships(self):
        placed_ships_1 = PlaceShips()
        generated_board_1 = placed_ships_1.get_ships_placement()
        player_ships_1 = placed_ships_1.get_ships()
        generated_board_2 = placed_ships_1.get_ships_placement()
        player_ships_2 = placed_ships_1.get_ships()

        placed_ships_3 = PlaceShips()
        generated_board_3 = placed_ships_3.get_ships_placement()
        self.assertNotEqual(generated_board_1, generated_board_3)

        self.assertEqual(player_ships_1, player_ships_2)
        self.assertEqual(generated_board_1, generated_board_2)


class ExecuteMovesTest(unittest.TestCase):
    def test_player_move(self):
        placed_ships = PlaceShips()
        generated_board = placed_ships.get_ships_placement()
        player_ships = placed_ships.get_ships()

        ship_board = ShipBoard(generated_board, player_ships)
        hit_board = HitBoard()

        boards = BoardsContainer(ship_board, hit_board, ship_board, hit_board)
        service = ExecuteMoves(boards, "random")
        player_ship_board = service.get_player_ship_board()
        player_hit_board = service.get_player_hit_board()
        computer_ship_board = service.get_computer_ship_board()
        computer_hit_board = service.get_computer_hit_board()

        self.assertEqual(player_ship_board.get_ship_layer(), generated_board)
        self.assertEqual(computer_ship_board.get_ship_layer(), generated_board)

        service.player_move(0, 0)
        self.assertEqual(player_hit_board.get_hit_layer(), computer_ship_board.get_hit_layer())

        service.player_move(0, 1)
        self.assertEqual(player_hit_board.get_hit_layer(), computer_ship_board.get_hit_layer())

    def test_computer_move(self):
        placed_ships = PlaceShips()
        generated_board = placed_ships.get_ships_placement()
        player_ships = placed_ships.get_ships()

        ship_board = ShipBoard(generated_board, player_ships)
        hit_board = HitBoard()

        boards = BoardsContainer(ship_board, hit_board, ship_board, hit_board)
        service = ExecuteMoves(boards, 'random')
        player_ship_board = service.get_player_ship_board()
        player_hit_board = service.get_player_hit_board()
        computer_ship_board = service.get_computer_ship_board()
        computer_hit_board = service.get_computer_hit_board()

        self.assertEqual(player_ship_board.get_ship_layer(), generated_board)
        self.assertEqual(computer_ship_board.get_ship_layer(), generated_board)

        service.computer_move()
        self.assertEqual(computer_hit_board.get_hit_layer(), player_ship_board.get_hit_layer())

        service.computer_move()
        self.assertEqual(computer_hit_board.get_hit_layer(), player_ship_board.get_hit_layer())

    def test_game_over(self):
        placed_ships = PlaceShips()
        generated_board = placed_ships.get_ships_placement()
        player_ships = placed_ships.get_ships()

        ship_board = ShipBoard(generated_board, player_ships)
        hit_board = HitBoard()

        boards = BoardsContainer(ship_board, hit_board, ship_board, hit_board)
        service = ExecuteMoves(boards, 'random')
        player_ship_board = service.get_player_ship_board()
        player_hit_board = service.get_player_hit_board()
        computer_ship_board = service.get_computer_ship_board()
        computer_hit_board = service.get_computer_hit_board()

        self.assertEqual(player_ship_board.get_ship_layer(), generated_board)
        self.assertEqual(computer_ship_board.get_ship_layer(), generated_board)

        self.assertEqual(service.game_over(), False)

        for i in range(10):
            for j in range(10):
                service.player_move(i, j)

        self.assertEqual(service.game_over(), True)

    def test_get_winner(self):
        placed_ships = PlaceShips()
        generated_board = placed_ships.get_ships_placement()
        player_ships = placed_ships.get_ships()

        ship_board = ShipBoard(generated_board, player_ships)
        hit_board = HitBoard()

        boards = BoardsContainer(ship_board, hit_board, ship_board, hit_board)
        service = ExecuteMoves(boards, 'random')
        player_ship_board = service.get_player_ship_board()
        player_hit_board = service.get_player_hit_board()
        computer_ship_board = service.get_computer_ship_board()
        computer_hit_board = service.get_computer_hit_board()

        self.assertEqual(player_ship_board.get_ship_layer(), generated_board)
        self.assertEqual(computer_ship_board.get_ship_layer(), generated_board)

        self.assertEqual(service.game_over(), False)

        for i in range(10):
            for j in range(10):
                service.player_move(i, j)

        self.assertEqual(service.game_over(), True)
        self.assertEqual(service.get_winner(), "Player")


if __name__ == '__main__':
    unittest.main()
