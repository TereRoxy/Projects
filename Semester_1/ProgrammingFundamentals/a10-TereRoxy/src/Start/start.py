from src.Assets.player_assets import ShipBoard
from src.Assets.player_assets import HitBoard
from src.Gameplay.generate_board import PlaceShips
from src.Gameplay.execute_moves import *
from src.UI.Console.ConsoleUI import ConsoleInterface
from configparser import ConfigParser
from src.UI.Graphical.GUI import GUI

class Settings:
    def __init__(self, file_name):
        self.UI = 'console'
        self.computer_strategy = None
        self.file_name = file_name
        self.theme = 'default'

    def get_ui(self):
        return self.UI

    def get_computer_strategy(self):
        return self.computer_strategy

    def load_settings(self):
        config = ConfigParser()
        config.read(self.file_name)

        self.UI = config["Settings"]["ui"]
        self.computer_strategy = config["Settings"]["computer_strategy"]
        self.theme = config["Settings"]["theme"]

def init_components():
    placed_ships = PlaceShips()
    generated_board = placed_ships.get_ships_placement()
    # print(generated_board)
    player_ships = placed_ships.get_ships()

    ship_board = ShipBoard(generated_board, player_ships)
    hit_board = HitBoard()

    return ship_board, hit_board


def run():
    settings = Settings("settings.properties")
    settings.load_settings()

    player_components = init_components()
    player_ship_board = player_components[0]
    player_hit_board = player_components[1]

    computer_components = init_components()
    computer_ship_board = computer_components[0]
    computer_hit_board = computer_components[1]

    container = BoardsContainer(player_ship_board, player_hit_board, computer_ship_board, computer_hit_board)

    computer_strategy = settings.get_computer_strategy()
    print(computer_strategy)
    service = ExecuteMoves(container, computer_strategy)
    theme = settings.theme

    if settings.get_ui() == 'console':
        UI = ConsoleInterface(service)
    elif settings.get_ui() == 'graphical':
        UI = GUI(service, theme)
    else:
        raise ValueError("Invalid UI type! Please check the settings.properties file.")
    UI.run()


if __name__ == "__main__":
    run()
