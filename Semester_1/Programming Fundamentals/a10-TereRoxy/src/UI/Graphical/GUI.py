import pygame
import sys
from src.UI.Graphical.Themes import ThemeColors
from src.UI.Graphical.WindowProperties import Window


class GUI:
    def __init__(self, service, theme='default'):
        self.__service = service
        self.__theme = theme
        self.player_board_ships = self.__service.get_player_ship_board().get_ship_layer()
        self.player_board_hits = self.__service.get_player_ship_board().get_hit_layer()
        self.opponent_board_hits = self.__service.get_player_hit_board().get_hit_layer()
        self.opponent_ship_board = self.__service.get_computer_ship_board()

        self.gameplay_screen = True

        self.Window = Window()
        pygame.init()
        self.screen = pygame.display.set_mode((self.Window.WIDTH, self.Window.HEIGHT))
        pygame.display.set_caption("Battleships")

        icon_image = pygame.image.load("battleship.png")
        pygame.display.set_icon(icon_image)
        self.ThemeColors = ThemeColors(theme)

        self.ship_message = "Click on a cell to fire a shot!"

        self.clock = pygame.time.Clock()

    def draw_grid_lines(self):

        for index in range(self.Window.GRID_SIZE + 1):
            coords = self.Window.grid_lines_player(index, 'vertical')
            pygame.draw.line(self.screen, self.ThemeColors.grid_line_color, coords[0], coords[1], 1)

            coords = self.Window.grid_lines_player(index, 'horizontal')
            pygame.draw.line(self.screen, self.ThemeColors.grid_line_color, coords[0], coords[1], 1)

            coords = self.Window.grid_lines_opponent(index, 'vertical')
            pygame.draw.line(self.screen, self.ThemeColors.grid_line_color, coords[0], coords[1], 1)

            coords = self.Window.grid_lines_opponent(index, 'horizontal')
            pygame.draw.line(self.screen, self.ThemeColors.grid_line_color, coords[0], coords[1], 1)

    def draw_boards(self):
        for row in range(self.Window.GRID_SIZE):
            for col in range(self.Window.GRID_SIZE):
                # Draw player's board
                rectangle = self.Window.cell_coordinates(row, col, 'player')
                pygame.draw.rect(self.screen, self.ThemeColors.grid_color, rectangle)
                self.draw_player_cell(row, col)

                # Draw opponent's board
                rectangle = self.Window.cell_coordinates(row, col, 'opponent')
                pygame.draw.rect(self.screen, self.ThemeColors.grid_color, rectangle)
                self.draw_opponent_cell(row, col)

    def pick_color(self, value):
        # 1 - hit, 2 - sunk, -1 - miss
        if value == 1:
            return self.ThemeColors.hit_color
        elif value == 2:
            return self.ThemeColors.sunk_ship_color
        elif value == -1:
            return self.ThemeColors.miss_color
        else:
            return None

    def draw_player_cell(self, row, col):
        # Draw the ship on the cell
        if 2 <= self.player_board_ships.content[row][col] <= 5:
            color_option = self.player_board_ships.content[row][col] - 2
            rectangle = self.Window.cell_coordinates(row, col, 'player')
            pygame.draw.rect(self.screen, self.ThemeColors.ship_color[color_option], rectangle)

        # Draw the hit on the cell
        circle_color = self.pick_color(self.player_board_hits.content[row][col])

        if circle_color is not None:
            pygame.draw.circle(self.screen, circle_color, self.Window.circle_center(row, col, 'player'),
                               self.Window.CIRCLE_RADIUS)

    def draw_opponent_cell(self, row, col):
        # Draw the hit on the cell
        circle_color = self.pick_color(self.opponent_board_hits.content[row][col])

        if circle_color is not None:
            pygame.draw.circle(self.screen, circle_color, self.Window.circle_center(row, col, 'opponent'),
                               self.Window.CIRCLE_RADIUS)

    def draw_ship_symbol(self):
        for row in range(self.Window.GRID_SIZE):
            for col in range(self.Window.GRID_SIZE):
                if self.show_ship_symbol(row, col):
                    ship = self.opponent_ship_board.get_ship_by_coordinate(col, row)
                    font = pygame.font.Font(None, 36)
                    label = font.render(ship.Symbol(), True,
                                        self.ThemeColors.foreground_color)

                    rectangle = label.get_rect(center=self.Window.ship_label_center(row, col))
                    self.screen.blit(label, rectangle)

    def show_ship_symbol(self, row, col):
        if not (2 <= self.opponent_ship_board.get_ship_layer().content[row][col] <= 5):
            return False
        elif self.opponent_board_hits.content[row][col] == 1:
            return True
        elif self.opponent_board_hits.content[row][col] == 2:
            return True
        else:
            return False

    def draw_ship_message(self, message):
        font = pygame.font.Font(None, 36)
        text = font.render(message, True, self.ThemeColors.foreground_color)
        self.screen.blit(text, (self.Window.BOARD_MARGIN, self.Window.BOARD_MARGIN))

    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    x, y = event.pos
                    self.handle_click(x, y)

            self.screen.fill(self.ThemeColors.background_color)
            self.draw_boards()
            self.draw_grid_lines()
            self.draw_ship_symbol()
            self.draw_ship_message(self.ship_message)

            pygame.display.flip()
            self.clock.tick(self.Window.FPS)

            if self.__service.game_over():
                self.draw_ship_message("")
                winner = self.__service.get_winner()
                self.game_over(winner)

    def game_over(self, winner):
        font = pygame.font.Font(None, 36)
        text = font.render("Game Over! {} won!".format(winner), True, self.ThemeColors.foreground_color)
        self.screen.blit(text, (self.Window.WIDTH // 2, self.Window.BOARD_MARGIN))
        pygame.display.flip()
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

    def handle_click(self, x, y):
        col, row = self.Window.click_coordinates(x, y)

        if col is None or row is None:
            return
        else:
            # Send the coordinates to the game backend for processing
            try:
                ship = self.__service.player_move(col, row)
                if ship is not None:
                    self.ship_message = ("You hit a {}! ".format(ship.Name()) + "({}, ".format(ship.Symbol())
                                         + "Size {}) ".format(ship.Length()))
                    if ship.sunk is True:
                        self.ship_message = "You sunk a {}!".format(ship.Name())
                else:
                    self.ship_message = "You missed!"

                self.__service.computer_move()
            except Exception as e:
                print(e)
                pass
