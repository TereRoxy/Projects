class Window:
    def __init__(self):
        self.GRID_SIZE = 10
        self.CELL_SIZE = 50
        self.CIRCLE_RADIUS = 25
        self.BOARD_MARGIN = 20
        self.WIDTH = self.GRID_SIZE * self.CELL_SIZE * 2 + self.CELL_SIZE * 3 + self.BOARD_MARGIN * 2
        self.HEIGHT = (self.GRID_SIZE + 1) * self.CELL_SIZE + self.BOARD_MARGIN * 2
        self.FPS = 60

    def circle_center(self, row, col, board):
        if board == 'player':
            return (col * self.CELL_SIZE + self.CELL_SIZE // 2 + self.BOARD_MARGIN, row * self.CELL_SIZE +
                    self.CELL_SIZE // 2 + self.CELL_SIZE + self.BOARD_MARGIN)
        elif board == 'opponent':
            return (col * self.CELL_SIZE + self.CELL_SIZE // 2 + self.CELL_SIZE * (self.GRID_SIZE + 2) +
                    self.BOARD_MARGIN * 2, row * self.CELL_SIZE + self.CELL_SIZE // 2 + self.CELL_SIZE +
                    self.BOARD_MARGIN)

    def grid_lines_player(self, index, direction):
        if direction == 'vertical':
            return ((index * self.CELL_SIZE + self.BOARD_MARGIN, self.CELL_SIZE + self.BOARD_MARGIN),
                    (index * self.CELL_SIZE + self.BOARD_MARGIN,
                     self.GRID_SIZE * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN))
        elif direction == 'horizontal':
            return ((self.BOARD_MARGIN, index * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN),
                    (self.GRID_SIZE * self.CELL_SIZE + self.BOARD_MARGIN, index * self.CELL_SIZE + self.CELL_SIZE +
                     self.BOARD_MARGIN))

    def grid_lines_opponent(self, index, direction):
        if direction == 'vertical':
            return ((index * self.CELL_SIZE + self.CELL_SIZE * (self.GRID_SIZE + 2) + self.BOARD_MARGIN * 2,
                     self.CELL_SIZE + self.BOARD_MARGIN),
                    (index * self.CELL_SIZE + self.CELL_SIZE * (self.GRID_SIZE + 2) + self.BOARD_MARGIN * 2,
                     self.GRID_SIZE * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN))
        elif direction == 'horizontal':
            return ((self.CELL_SIZE * (self.GRID_SIZE + 2) + self.BOARD_MARGIN * 2,
                     index * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN),
                    (self.GRID_SIZE * self.CELL_SIZE + self.CELL_SIZE * (self.GRID_SIZE + 2) + self.BOARD_MARGIN * 2,
                     index * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN))

    def cell_coordinates(self, row, col, board):
        if board == 'player':
            # (col * CELL_SIZE + BOARD_MARGIN, row * CELL_SIZE + CELL_SIZE + BOARD_MARGIN, CELL_SIZE, CELL_SIZE))
            return (col * self.CELL_SIZE + self.BOARD_MARGIN,
                    row * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN,
                    self.CELL_SIZE,
                    self.CELL_SIZE)
        elif board == 'opponent':
            return (col * self.CELL_SIZE + self.CELL_SIZE * (self.GRID_SIZE + 2) + self.BOARD_MARGIN * 2,
                    row * self.CELL_SIZE + self.CELL_SIZE + self.BOARD_MARGIN,
                    self.CELL_SIZE,
                    self.CELL_SIZE)

    def click_coordinates(self, x, y):
        col = (x - (4 * self.BOARD_MARGIN + self.GRID_SIZE * self.CELL_SIZE)) // self.CELL_SIZE - 1
        row = (y - self.BOARD_MARGIN) // self.CELL_SIZE - 1

        # Check if the click is inside the grid
        if 0 <= col < self.GRID_SIZE and 0 <= row < self.GRID_SIZE:
            return col, row
        else:
            return None, None

    def ship_label_center(self, row, col):
        return (self.BOARD_MARGIN * 2 + (self.GRID_SIZE + 2) * self.CELL_SIZE + col * self.CELL_SIZE + self.CELL_SIZE // 2,
                self.BOARD_MARGIN + self.CELL_SIZE + self.CELL_SIZE * row + self.CELL_SIZE // 2)