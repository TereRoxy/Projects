BATTLESHIPS GAME
================
Author: TEREBENT ROXANA-ALEXANDRA  
Group: 917  
Year: 2023-2024

----------
DESCRIPTION   
---------------
Battleships is a guessing strategy game for two players (computer and human player).

The game is played on 4 boards:  
- 2 visible boards (for the player):
  - 1 board marked with the player's fleet and the shots the computer made against the player
  - 1 board marked with the player's shots against the computer
- 2 hidden boards (used by the computer):  
    - 1 board for the computer's fleet and the shots the player made against the computer
    - 1 board for the computer's shots against the player

Both the player and the computer have 10 ships: 1 carrier, 2 battleships, 3 cruisers and 4 destroyers.

At the beginning of the game, the ships of both the computer and the player are placed randomly on the board.
It is guaranteed that the ships do not overlap (only one ship can occupy any given cell in the grid) and are not placed diagonally.

The locations of the computer's fleets are concealed from the human player and vice-versa. 
Players alternate turns calling "shots" at the other player's ships, and the objective of the game is to destroy the opposing player's fleet.
To shoot, the player enters the coordinates of the cell he wants to shoot at. The coordinates are given as a letter and a number.
After each shot, the player is notified if he hit or missed a ship.
After the player shoots, the computer shoots in its turn and retrieves the hit/miss information.

A ship is "sunk" when all the cells it occupies have been hit. The player who sunk the ship is notified what kind of ship is sunk.
The game ends when one player's fleet is destroyed. The player who destroyed the other player's fleet wins the game.

**NB!** Personal addition to the game: in order to make the game more strategic, the player is also informed 
of the __kind of ship__ that was hit after each shot (carrier, battleship, cruiser or destroyer). 
This allows the player to make more informed decisions when shooting at the computer's fleet.

----------

**BOARD**  
- size: 10x10 (rows x columns):  
  - rows: 1 - 10
  - columns: A - J

-----------

**SHIPS**
1. ***_Carrier_***
    - size: 5
    - number of ships: 1
2. ***_Battleship_***
    - size: 4
    - number of ships: 2
3. ***_Cruiser_***
    - size: 3
    - number of ships: 3
4. ***_Destroyer_***
    - size: 2
    - number of ships: 4

Total number of ships: 10  
Total number of occupied cells: 30

---------------

**CONSOLE GAMEPLAY**

UI symbols used in the game:
- empty cell: `.`
- missed shot: `X`
- hit shot: `O`
- player ship: `-`
- computer's sunk ship: `#`

The game starts with the player's turn. The player is asked to enter the coordinates of the cell he wants to shoot at.
The coordinates are given as a letter and a number. An example of a valid input is `A1`. 
Invalid inputs are handled by the program which outputs an error.

--------------

**GRAPHICAL GAMEPLAY**

Two boards are displayed on the screen: the player's board with the ships on the left and the opponent's board
on the right. The opponent's board displays the shots the player made against the computer.

The game starts with the player's turn. The player is asked to click on the cell he wants to shoot at. After the shot
is made, the computer takes a shot. A shot is represented by a circle on the board. If the shot is a hit, the circle
is black, and it contains the symbol of the ship that has been hit. If the shot is a miss, the circle is white. 
If the shot sinks a ship, the circles on the ship turn red.

The symbols represent the following:
- carrier: `C`
- battleship: `B`
- cruiser: `R`
- destroyer: `D`

When the game ends, the winner is announced and the game stops.
