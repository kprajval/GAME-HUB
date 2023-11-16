#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for time assignments
#include <windows.h> // used for sleep inbuit function

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
}

int tic_tac_toe() {
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
                    printf("Amount lost: %d\n", -game_node.balance);
                } else {
                    printf("Amount to take back home: %d\n", game_node.balance);
                }
                printf("Total wins: %d\n", game_node.won);
                printf("Total losses: %d\n", game_node.lost);
                printf("Win percentage: %.2f%%\n", (game_node.won * 100.0 / (game_node.won + game_node.lost)));
                printf("Thank you for visiting MADZCASINO!\n");
                return 0;

            default:
                printf("Please enter a valid choice.\n");
                break;
        }
    }

    return 0;
}