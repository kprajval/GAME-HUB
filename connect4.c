#include <stdio.h>
#include <stdbool.h>

#define ROWS 6
#define COLUMNS 7

typedef struct {
    char gameBoard[ROWS][COLUMNS];
    int currentPlayer;
    int totalMoves;
} Connect4Game;

void initialize(Connect4Game *game) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            game->gameBoard[i][j] = ' ';
        }
    }
    game->currentPlayer = 1;
    game->totalMoves = 0;
}

void printGameBoard(Connect4Game *game) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("| %c ", game->gameBoard[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < COLUMNS; j++) {
        printf("  %d ", j + 1);
    }
    printf("\n");
}

bool isColumnFull(Connect4Game *game, int col) {
    return game->gameBoard[0][col] != ' ';
}

bool checkWin(Connect4Game *game, char playerSymbol) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (game->gameBoard[i][j] == playerSymbol) {
                // Check horizontally
                if (j + 3 < COLUMNS &&
                    game->gameBoard[i][j + 1] == playerSymbol &&
                    game->gameBoard[i][j + 2] == playerSymbol &&
                    game->gameBoard[i][j + 3] == playerSymbol) {
                    return true;
                }
                // Check vertically
                if (i + 3 < ROWS &&
                    game->gameBoard[i + 1][j] == playerSymbol &&
                    game->gameBoard[i + 2][j] == playerSymbol &&
                    game->gameBoard[i + 3][j] == playerSymbol) {
                    return true;
                }
                // Check diagonally (up-right)
                if (i + 3 < ROWS && j + 3 < COLUMNS &&
                    game->gameBoard[i + 1][j + 1] == playerSymbol &&
                    game->gameBoard[i + 2][j + 2] == playerSymbol &&
                    game->gameBoard[i + 3][j + 3] == playerSymbol) {
                    return true;
                }
                // Check diagonally (up-left)
                if (i + 3 < ROWS && j - 3 >= 0 &&
                    game->gameBoard[i + 1][j - 1] == playerSymbol &&
                    game->gameBoard[i + 2][j - 2] == playerSymbol &&
                    game->gameBoard[i + 3][j - 3] == playerSymbol) {
                    return true;
                }
            }
        }
    }
    return false;
}

void dropPiece(Connect4Game *game, int col) {
    int row = ROWS - 1;
    while (row >= 0 && game->gameBoard[row][col] != ' ') {
        row--;
    }
    if (row >= 0) {
        game->gameBoard[row][col] = (game->currentPlayer == 1) ? 'X' : 'O';
        game->currentPlayer = 3 - game->currentPlayer;
        game->totalMoves++;
    }
}

void displayGameExplanation() {
    printf("Welcome to Connect 4!\n");
    printf("Players choose X or O. Drop your discs into the grid, starting in the middle or at the edge, ");
    printf("to stack your discs upwards, horizontally, or diagonally. Use strategy to block opponents while ");
    printf("aiming to be the first player to get 4 in a row to win.\n");
}

int connect4() {
    Connect4Game game;
    initialize(&game);

    int selectedColumn;
    bool validMove = false;

    displayGameExplanation();

    while (game.totalMoves < ROWS * COLUMNS) {
        printGameBoard(&game);

        do {
            printf("Player %d, enter column (1-%d): ", game.currentPlayer, COLUMNS);
            if (scanf("%d", &selectedColumn) != 1 || selectedColumn < 1 || selectedColumn > COLUMNS) {
                while (getchar() != '\n');
            } else {
                selectedColumn--;
                if (!isColumnFull(&game, selectedColumn)) {
                    validMove = true;
                } else {
                    printf("Column %d is full. Try again.\n", selectedColumn + 1);
                }
            }
        } while (!validMove);

        dropPiece(&game, selectedColumn);

        if (checkWin(&game, 'X')) {
            printGameBoard(&game);
            printf("Player 1 (X) wins!\n");
            break;
        } else if (checkWin(&game, 'O')) {
            printGameBoard(&game);
            printf("Player 2 (O) wins!\n");
            break;
        }
    }

    if (game.totalMoves == ROWS * COLUMNS) {
        printGameBoard(&game);
        printf("It's a draw!\n");
    }

    return 0;
}