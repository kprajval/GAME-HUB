#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

struct TicTacToe {
    char grid[SIZE][SIZE];
};

void initBoard(struct TicTacToe *game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            game->grid[i][j] = ' ';
        }
    }
}

void displayBoard(struct TicTacToe game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", game.grid[i][j]);
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            for (int k = 0; k < SIZE * 4 - 1; k++) {
                printf("-");
            }
            printf("\n");
        }
    }
}

bool checkWin(struct TicTacToe game, char player) {
    // Check rows and columns for a win
    for (int i = 0; i < SIZE; i++) {
        if (game.grid[i][0] == player && game.grid[i][1] == player && game.grid[i][2] == player) {
            return true; // Row win
        }
        if (game.grid[0][i] == player && game.grid[1][i] == player && game.grid[2][i] == player) {
            return true; // Column win
        }
    }

    // Check diagonals for a win
    if (game.grid[0][0] == player && game.grid[1][1] == player && game.grid[2][2] == player) {
        return true; // Diagonal from top-left to bottom-right
    }
    if (game.grid[0][2] == player && game.grid[1][1] == player && game.grid[2][0] == player) {
        return true; // Diagonal from top-right to bottom-left
    }

    return false;
}

void makeMove(struct TicTacToe *game, int row, int col, char player) {
    if (game->grid[row][col] == ' ') {
        game->grid[row][col] = player;
    } else {
        printf("Invalid move. Try again.\n");
    }
}

int tic_tac_toe() {
    struct TicTacToe game;
    char currentPlayer = 'X';
    int totalMoves = 0;
    bool gameEnded = false;

    initBoard(&game);

    printf("Welcome to 3x3 Tic-Tac-Toe! Connect 3 to win.\n");

    while (!gameEnded) {
        printf("Current board:\n");
        displayBoard(game);

        int row, col;
        printf("Player %c, enter row and column (0-2): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid input. Row and column must be between 0 and 2.\n");
            continue;
        }

        makeMove(&game, row, col, currentPlayer);
        totalMoves++;

        if (checkWin(game, currentPlayer)) {
            printf("Player %c wins!\n", currentPlayer);
            gameEnded = true;
        } else if (totalMoves == SIZE * SIZE) {
            printf("It's a draw!\n");
            gameEnded = true;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printf("Final board:\n");
    displayBoard(game);

    return 0;
}
