Tic-Tac-Toe Game in C++

This is a classic Tic-Tac-Toe game implemented in C++ that runs in the command line. It offers multiple modes, including Player vs. Player and Player vs. CPU, along with features like saving progress, undoing moves, and score tracking.

Features

Game Modes:
Player vs. Player: Two players can compete against each other.
Player vs. CPU: Play against a computer opponent (as indicated by `CPU Mode.h`).
Score Tracking: The game keeps track of the scores for Player 1 (X) and Player 2 (O).
Save & Load Game: You can save the current state of a game and load it later to continue playing.
Undo Move: Players have the option to undo their last move.
Color-Coded Interface: The game board and player turns are displayed with colors for a better user experience.
Play Again: After a game ends, you can choose to play another round.

How to Compile and Run

To compile and run this game, you will need a C++ compiler (like g++).

1.  Save the code: Make sure you have the main file (`Tic Tac Toe (Main Code).cpp`) and the header file (`CPU Mode.h`) in the same directory.

2.  Open a terminal or command prompt.

3.  Navigate to the directory where you saved the files.

4.  Compile the code using the following command:

    g++ "Tic Tac Toe (Main Code).cpp" -o TicTacToe

Note: The use of < conio.h> might cause compilation errors on non-Windows systems (like Linux or macOS). You may need to find an alternative or remove its usage for it to compile on those platforms.*

5.  Run the executable:
    ./TicTacToe
    On Windows, you might just type:
    TicTacToe

How to Play

1.  When you start the game, you will see a main menu with options to Start Game, Load Game, or Exit.
2.  If you start a new game, you can choose between Player vs. Player and Player vs. CPU modes.
3.  The game board is displayed with numbers from 1 to 9 representing the cells.
4.  To make a move, enter the number of the cell where you want to place your mark (X or O).
5.  After each move, you will be asked if you want to undo it.
6.  The first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins the game.
7.  If all cells are filled and no player has won, the game is a draw.
8.  The game will keep track of the score and ask if you want to play again.

File Structure
Tic Tac Toe (Main Code).cpp: The main source file containing the game logic for the board, player turns, and the Player vs. Player mode.
CPU Mode.h: A header file that presumably contains the logic for the Player vs. CPU game mode.
Player vs Player.txt: A text file automatically generated to save the state of a Player vs. Player game.


