class Colors:
    def __init__(self):
        self.WHITE = (248, 248, 248)
        self.BLACK = (46, 40, 42)
        self.BLUE = (125, 83, 222)
        self.RED = (249, 57, 67)
        self.GRAY = (161, 166, 180)

        self.ORANGE = (229, 88, 18)
        self.YELLOW = (255, 210, 63)
        self.LIGHT_BLUE = (137, 166, 251)
        self.VIOLET = (164, 44, 214)
        self.LIGHT_GREEN = (180, 237, 210)


class ThemeColors:
    def __init__(self, theme='default'):
        self.colors = Colors()
        self.__theme = theme
        self.set_theme(theme)

    def dark_theme(self):
        self.__theme = 'dark'
        self.background_color = self.colors.BLACK
        self.foreground_color = self.colors.WHITE
        self.grid_color = self.colors.GRAY
        self.grid_line_color = self.colors.WHITE
        self.hit_color = self.colors.BLACK
        self.miss_color = self.colors.WHITE
        self.ship_color = [self.colors.ORANGE, self.colors.YELLOW, self.colors.LIGHT_BLUE, self.colors.VIOLET,
                            self.colors.LIGHT_GREEN]
        self.sunk_ship_color = self.colors.RED

    def default_theme(self):
        self.__theme = 'default'
        self.background_color = self.colors.WHITE
        self.foreground_color = self.colors.BLACK
        self.grid_color = self.colors.GRAY
        self.grid_line_color = self.colors.BLACK
        self.hit_color = self.colors.BLACK
        self.miss_color = self.colors.WHITE
        self.ship_color = [self.colors.ORANGE, self.colors.YELLOW, self.colors.LIGHT_BLUE, self.colors.VIOLET,
                            self.colors.LIGHT_GREEN]
        self.sunk_ship_color = self.colors.RED

    def set_theme(self, theme):
        if theme == 'dark':
            self.dark_theme()
        else:
            self.default_theme()
