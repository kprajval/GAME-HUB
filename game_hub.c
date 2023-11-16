#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>

// CASINO
typedef struct hist {
    char *operation;
    char *result;
    struct hist *next;
} HIST;

typedef struct casino {
    char name[20];
    int balance;
    HIST *history;
    int won;
    int lost;
    float luck_percentage;
} CASINO;

CASINO *init(CASINO *game_node) {
    game_node->won = game_node->lost = 0;
    game_node->luck_percentage = 0.0;
    game_node->balance = 0;
    game_node->history = NULL;
    return game_node;
}

HIST *create(char *op, char *result) {
    HIST *temp = (HIST *)malloc(sizeof(HIST));
    temp->operation = strdup(op);
    temp->result = strdup(result);
    temp->next = NULL;
    return temp;
}

void insert(CASINO *game_node, HIST *temp) {
    if (game_node->history == NULL) {
        game_node->history = temp;
    } else {
        HIST *cur = game_node->history;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = temp;
    }
}

void deposit(CASINO *game_node) {
    int amt;
    printf("%s, how much would you like to deposit: ", game_node->name);
    scanf("%d", &amt);
    game_node->balance += amt;

    HIST *temp = create("Deposit", "Success");
    insert(game_node, temp);
}

void balance(CASINO *game_node) {
    printf("%s, your current balance: %d\n", game_node->name, game_node->balance);
}

void bet(CASINO *game_node) {
    int bet_amt, bet_choice;

    printf("%s, enter your bet amount: ", game_node->name);
    scanf("%d", &bet_amt);

    printf("%s, make your guess: ", game_node->name);
    scanf("%d", &bet_choice);

    int out = rand() % 22;
    if (out == bet_choice) {
        printf("**** Congratulations! ****\nYou've won 2x your bet amount!\n");
        game_node->balance = game_node->balance + bet_amt;
        game_node->won++;
        game_node->balance += 2 * bet_amt;
        balance(game_node);
        HIST *temp = create("Betting", "Win");
        insert(game_node, temp);
    } else {
        printf("**** Better luck next time! ****\n");
        game_node->balance = game_node->balance - bet_amt;
        game_node->lost++;
        game_node->balance -= bet_amt;
        balance(game_node);
        HIST *temp = create("Betting", "Lost");
        insert(game_node, temp);
    }
}

void history(CASINO *game_node) {
    HIST *cur = game_node->history;
    if (cur == NULL) {
        printf("%s, you haven't performed any operations yet.\n", game_node->name);
    } else {
        printf("%s, here's your history:\n", game_node->name);
        while (cur != NULL) {
            printf("Operation: %s, Result: %s\n", cur->operation, cur->result);
            cur = cur->next;
        }
    }
}

void rules() {
    printf("Welcome to MADZCASINO! Here are the rules of the game\n\n");
    printf("1. You can deposit money at any time during the game.\n");
    printf("2. You can check your current balance at any point in the game.\n");
    printf("3. When you win a bet, your winnings are doubled, and when you lose, your bet amount is deducted.\n");
    printf("4. Your choice has to be made between 0 to 21\n");
    printf("5. You can view your history of operations made by selecting 'View History'.\n");
    printf("6. To exit the game, simply choose the 'Quit' option, and your final results will be displayed.\n\n");
    printf("**** Have a great time at MADZCASINO! Good luck and gamble responsibly! ****\n");
}

void animate(int delay) {
    printf("Processing");
    for (int i = 0; i < 3; i++) {
        Sleep(delay);
        printf(".");
    }
    printf("\n");
}

void casino() {
    CASINO game_node;
    int choice;

    srand(time(NULL));

    init(&game_node);

    printf("\n");
    rules();
    printf("\n");

    printf("Enter your player name: ");
    scanf("%s", game_node.name);

    printf("Welcome to MADZCASINO, %s!\n", game_node.name);

    while (1) {
        printf("\n1. Deposit\n2. Check Balance\n3. Place a Bet\n4. View History\n5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Depositing funds... ");
                animate(1000);
                deposit(&game_node);
                break;

            case 2:
                printf("Checking balance... ");
                animate(1000);
                balance(&game_node);
                break;

            case 3:
                printf("Placing a bet... ");
                animate(1000);
                bet(&game_node);
                break;

            case 4:
                printf("Viewing history... ");
                animate(1000);
                history(&game_node);
                break;

            case 5:
                printf("Quitting... ");
                animate(1000);
                printf("\nHere are your end results:\n");
                if (game_node.balance < 0) {
                    printf("You owe MADZCASINO: %d\n", game_node.balance);
                    game_node.balance = -game_node.balance;
                } else {
                    printf("You have won from MADZCASINO: %d\n", game_node.balance);
                }
                printf("Total wins: %d\n", game_node.won);
                printf("Total losses: %d\n", game_node.lost);
                game_node.luck_percentage = ((float)game_node.won / (float)(game_node.won + game_node.lost)) * 100;
                printf("Luck Percentage: %.2f%%\n", game_node.luck_percentage);
                printf("\nThank you for playing, %s! We hope to see you again.\n", game_node.name);
                return;

            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }
}

// CONNECT 4
#define ROWS 6
#define COLUMNS 7

void printBoard(char board[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
}

bool isBoardFull(char board[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool isValidMove(char board[ROWS][COLUMNS], int column) {
    if (column < 0 || column >= COLUMNS) {
        return false;
    }
    return (board[0][column] == ' ');
}

bool isWinningMove(char board[ROWS][COLUMNS], char player) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            // Check horizontally
            if (col + 3 < COLUMNS &&
                board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return true;
            }

            // Check vertically
            if (row + 3 < ROWS &&
                board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return true;
            }

            // Check diagonally (up-right)
            if (row + 3 < ROWS && col + 3 < COLUMNS &&
                board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return true;
            }

            // Check diagonally (up-left)
            if (row + 3 < ROWS && col - 3 >= 0 &&
                board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player) {
                return true;
            }
        }
    }
    return false;
}

void connect4() {
    char board[ROWS][COLUMNS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j] = ' ';
        }
    }

    bool player1Turn = true;
    bool gameOver = false;

    while (!gameOver) {
        // Print the current board
        printBoard(board);

        // Get the current player's symbol
        char playerSymbol = (player1Turn) ? 'X' : 'O';
        printf("%s's turn (%c): ", (player1Turn) ? "Player 1" : "Player 2", playerSymbol);

        // Get the player's move
        int column;
        scanf("%d", &column);

        if (isValidMove(board, column)) {
            // Make the move
            for (int i = ROWS - 1; i >= 0; i--) {
                if (board[i][column] == ' ') {
                    board[i][column] = playerSymbol;
                    break;
                }
            }

            // Check for a win
            if (isWinningMove(board, playerSymbol)) {
                printBoard(board);
                printf("%s wins!\n", (player1Turn) ? "Player 1" : "Player 2");
                gameOver = true;
            } else if (isBoardFull(board)) {
                // Check for a draw
                printBoard(board);
                printf("It's a draw!\n");
                gameOver = true;
            } else {
                // Switch to the other player's turn
                player1Turn = !player1Turn;
            }
        } else {
            printf("Invalid move. Please try again.\n");
        }
    }
}

// SNAKE
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
int life;
char key;

void record();
void load();
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate {
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500], food, body[30];

int snake() {
    char key;
    Print();
    system("cls");
    system("color 3f");
    load();
    length = 5;
    head.x = 25;
    head.y = 20;
    head.direction = RIGHT;
    Boarder();
    Food();
    life = 3;
    bend[0] = head;
    Move();
    return 0;
}

void Move() {
    int a, i;
    do {
        Food();
        fflush(stdin);
        len = 0;
        for (i = 0; i < 30; i++) {
            body[i].x = 0;
            body[i].y = 0;
            if (i == length) break;
        }
        Delay(length);
        Boarder();
        if (head.direction == RIGHT)
            Right();
        else if (head.direction == LEFT)
            Left();
        else if (head.direction == DOWN)
            Down();
        else if (head.direction == UP)
            Up();
        ExitGame();
    } while (!kbhit());
    a = getch();
    if (a == 27) {
        system("cls");
        exit(0);
    }
    key = getch();
    if ((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (key == LEFT && head.direction != RIGHT && head.direction != LEFT) || (key == UP && head.direction != DOWN && head.direction != UP) || (key == DOWN && head.direction != UP && head.direction != DOWN)) {
        bend_no++;
        bend[bend_no] = head;
        head.direction = key;
        if (key == UP)
            head.y--;
        if (key == DOWN)
            head.y++;
        if (key == RIGHT)
            head.x++;
        if (key == LEFT)
            head.x--;
        Move();
    } else if (key == 27) {
        system("cls");
        exit(0);
    } else {
        printf("\a");
        Move();
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GotoXY(int x, int y) {
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}

void load() {
    int row, col, r, c, q;
    gotoxy(36, 14);
    printf("Loading...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++) {
        for (q = 0; q <= 100000000; q++); // to display the character slowly
        printf("%c", 177);
    }
    getch();
}

void Down() {
    int i;
    for (i = 0; i <= (head.y - bend[bend_no].y) && len < length; i++) {
        GotoXY(head.x, head.y - i);
        if (len == 0)
            printf("v");
        else
            printf("*");
        body[len].x = head.x;
        body[len].y = head.y - i;
        len++;
    }
    Bend();
    if (!kbhit())
        head.y++;
}

void Delay(long double k) {
    Score();
    long double i;
    for (i = 0; i <= (10000000); i++);
}

void ExitGame() {
    int i, check = 0;
    for (i = 4; i < length; i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
            check++;
        }
        if (i == length || check != 0)
            break;
    }
    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0) {
        life--;
        if (life >= 0) {
            head.x = 25;
            head.y = 20;
            bend_no = 0;
            head.direction = RIGHT;
            Move();
        } else {
            system("cls");
            printf("All Lives Completed\nBetter Luck Next Time!!!\nPress Any Key To Quit The Game\n");
            record();
            exit(0);
        }
    }
}

void Food() {
    if (head.x == food.x && head.y == food.y) {
        length++;
        time_t a;
        a = time(0);
        srand(a);
        food.x = rand() % 70;
        if (food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if (food.y <= 10)
            food.y += 11;
    } else if (food.x == 0) {
        food.x = rand() % 70;
        if (food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if (food.y <= 10)
            food.y += 11;
    }
}

void Left() {
    int i;
    for (i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++) {
        GotoXY((head.x + i), head.y);
        if (len == 0)
            printf("<");
        else
            printf("*");
        body[len].x = head.x + i;
        body[len].y = head.y;
        len++;
    }
    Bend();
    if (!kbhit())
        head.x--;
}

void Right() {
    int i;
    for (i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++) {
        body[len].x = head.x - i;
        body[len].y = head.y;
        GotoXY(body[len].x, body[len].y);
        if (len == 0)
            printf(">");
        else
            printf("*");
        len++;
    }
    Bend();
    if (!kbhit())
        head.x++;
}

void Bend() {
    int i, j, diff;
    for (i = bend_no; i >= 0 && len < length; i++) {
        if (bend[i].x == bend[i - 1].x) {
            diff = bend[i].y - bend[i - 1].y;
            if (diff < 0) {
                for (j = 1; j <= (-diff); j++) {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y + j;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            } else if (diff > 0) {
                for (j = 1; j <= diff; j++) {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y - j;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            }
        } else if (bend[i].y == bend[i - 1].y) {
            diff = bend[i].x - bend[i - 1].x;
            if (diff < 0) {
                for (j = 1; j <= (-diff) && len < length; j++) {
                    body[len].x = bend[i].x + j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            } else if (diff > 0) {
                for (j = 1; j <= diff && len < length; j++) {
                    body[len].x = bend[i].x - j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            }
        }
    }
}

void Boarder() {
    system("cls");
    int i;
    GotoXY(food.x, food.y);
    printf("F");
    for (i = 10; i < 71; i++) {
        GotoXY(i, 10);
        printf("!");
        GotoXY(i, 30);
        printf("!");
    }
    for (i = 10; i < 31; i++) {
        GotoXY(10, i);
        printf("!");
        GotoXY(70, i);
        printf("!");
    }
}

void Print() {
    printf("Knowledge 360\n\n");
    printf("\tWelcome To The Snake Game.\n\n (Press Any Key To Continue...)\n");
    getch();
    system("cls");
    printf("\tGame Instructions:\n");
    printf("\n-> Use Arrow Keys To Move The Snake.\n\n-> You Will Be Provided Foods (F) at The random Coordinates Of The Screen Which You Have To Eat, To Make Score.\n");
    printf("Every time You Eat A Food The Length Of The Snake Will Be Increased By 1 Element indicating the score.");
    printf("\n\n-> Here You Are Provided With Three Lives. Your Life Will Decrease As You Hit The Wall Or Snake's Body.");
    printf("\n\n-> You Can Pause The Game While Playing By Pressing Any Key, To Continue The Paused Game Press Any Key Once Again.");
    printf("\n\n-> If You Want To Exit Press ESC.\n");
    printf("\n\n\nPress Any Key To Play The Game...");
    if (getch() == 27)
        exit(0);
}

void record() {
    char plname[20], nplname[20], cha, c;
    int i, j, px;
    FILE* info;
    info = fopen("record.txt", "a+");
    getch();
    system("cls");
    printf("Enter Your Name: ");
    scanf("%[^\n]", plname);
    for (j = 0; plname[j] != '\0'; j++) {
        nplname[0] = toupper(plname[0]);
        if (plname[j - 1] == ' ') {
            nplname[j] = toupper(plname[j]);
            nplname[j - 1] = plname[j - 1];
        } else {
            nplname[j] = plname[j];
        }
    }
    nplname[j] = '\0';
    fprintf(info, "\n\nPlayer Name: %s\n", nplname);
    time_t mytime;
    mytime = time(NULL);
    fprintf(info, "\nPlayed Date: %s", ctime(&mytime));
    fprintf(info, "Score: %d\n", px = Scoreonly());
    for (i = 0; i <= 50; i++)
        fprintf(info, "%c", '_');
    fprintf(info, "\n");
    fclose(info);
    printf("Press 'y' if you want to see past records (y/n): ");
    cha = getch();
    system("cls");
    if (cha == 'y') {
        info = fopen("record.txt", "r");
        do {
            putchar(c = getc(info));
        } while (c != EOF);
    }
    fclose(info);
}

int Score() {
    int score;
    GotoXY(20, 8);
    score = length - 5;
    printf("SCORE : %d", (length - 5));
    score = length - 5;
    GotoXY(50, 8);
    printf("Life : %d", life);
    return score;
}

int Scoreonly() {
    int score = Score();
    system("cls");
    return score;
}

void Up() {
    int i;
    for (i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++) {
        GotoXY(head.x, head.y + i);
        if (len == 0)
            printf("^");
        else
            printf("*");
        body[len].x = head.x;
        body[len].y = head.y + i;
        len++;
    }
    Bend();
    if (!kbhit())
        head.y--;
}

// TIC TAC TOE
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

//USER DETAILS

int main() {
    int choice;

    while (1) {
        printf("Choose a game to play:\n");
        printf("1. Casino\n");
        printf("2. Connect4\n");
        printf("3. Snake\n");
        printf("4. Tic-Tac-Toe\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                casino();
                break;

            case 2:
                connect4();
                break;

            case 3:
                snake();
                break;

            case 4:
                tic_tac_toe();
                break;

            case 5:
                printf("Quitting the game menu...\n");
                return 0;

            default:
                printf("Please enter a valid choice.\n");
                break;
        }
    }

    return 0;
}