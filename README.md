# 🎮 Tic-Tac-Toe 🎮

A classic Tic-Tac-Toe game implemented in C. This project is a simple, yet complete, command-line version of the game.

## 🛠️ Building the Game

This project uses `bmake` for building. On most BSD systems, `bmake` is the default `make`. On other systems, like GNU/Linux, you may need to install it.

**On BSD:**
```sh
make
```

**On GNU/Linux (with `bmake` installed):**
```sh
bmake
```

If you don't have `bmake`, you can likely still use GNU `make` as the `Makefile` is simple.

```sh
make
```

The build process will create a `ttt` executable in the project directory.

## 🚀 Running the Game

To start the game, run the following command in your terminal:

```sh
./ttt
```

## Code Details

The entire game is contained within `ttt.c`. Here is a breakdown of how the code works.

### `main` function

The `main` function is the entry point of the game. It initializes the game board, and then enters a loop that continues until the game is over. Inside the loop, it prints the board, gets the current player's move, and then checks if the game has been won or if it's a draw.

### Game Board

The game board is represented by a `char` array named `board` of size 9. Each element of the array corresponds to a square on the Tic-Tac-Toe board. The squares are numbered 1-9.

### Functions

*   **`print_board()`**: This function prints the current state of the game board to the console.
*   **`get_move()`**: This function prompts the current player to enter their move. It reads the input from the user and updates the `board` array.
*   **`check_win()`**: This function checks if the current player has won the game. It does this by checking all possible winning combinations (rows, columns, and diagonals).
*   **`check_draw()`**: This function checks if the game is a draw. A draw occurs when all squares on the board are filled, and no player has won.
*   **`game_over()`**: This is a utility function that is called when the game ends. It prints the final board and a message indicating the outcome of the game (win or draw).

The game alternates between player 'X' and player 'O', with 'X' starting first. The game ends when one player gets three in a row, or when all nine squares are filled.