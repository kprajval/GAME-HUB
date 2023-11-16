# GAME-HUB

**About the game** <br>
This Project is on  a Game Hub which will include 4 objectively and functionally different games which are fun to play either with others or alone.  In this project we have included a Casino game , Connect-4 , Tic-Tac-Toe and the Snake game where you can select which game you want to play and when you are done with the game you can switch to a different game. 
**Explanation on the selection of a game** : In the code we used a switch case function where it allows you to select between 1-4 for a game from the list. <br>
The switch statement is used to perform different actions based on the value of choice. Here's what each case does:
case 1: Calls a function casino() which presumably represents a casino game.
case 2: Calls a function connect4() for playing Connect Four.
case 3: Calls a function snake() for playing the Snake game.
case 4: Calls a function tic_tac_toe() for playing Tic-Tac-Toe.
case 5: Displays a message and returns 0, which effectively quits the program.If the user enters a number other than 1, 2, 3, 4, or 5, the default case is executed. It prints a message, "Please enter a valid choice."


**Explanation of Casino Game** <br>
This is a simple text-based casino game implemented in C. The game is called MADZCASINO and offers features such as depositing funds, checking balance, placing bets, viewing a history of operations, and quitting the game with end results. The player interacts with the game through a menu system, and the results are tracked, including the total amount won, lost, and win percentage. 
Code uses :  
  - Structures to organize player information 
  - Basic random module : used for generating random numbers 
  - This project includes small animation features using Windows API's sleep function.
Functioning :
  1. Initialization: - The program initializes a casino player by setting default values for various attributes such as the player's name, balance, and history.
  2. User Interaction Loop: - The program enters a loop where it repeatedly prompts the player to choose from various options, including depositing money, checking balance, placing bets, viewing history, or quitting         the game.
  3. Deposit:- If the player chooses to deposit money, they are prompted to enter an amount, and the program updates the player's balance accordingly. The deposit operation is recorded in the player's history.
  4. Check Balance:- The player can check their current balance at any time during the game.
  5. Place a Bet:- The player can place a bet by entering an amount and making a guess between 0 and 21. The outcome of the bet is determined randomly, and the player's balance is adjusted accordingly. The bet               operation and result are recorded in the player's history.
  6. View History:- The player can view a history of their operations, including details such as the type of operation (e.g., deposit, bet) and the result (e.g., win, loss).
  7. Quitting the Game:- If the player chooses to quit, the program displays final results, including the total balance (whether the player won or lost), the number of wins and losses, and the luck percentage                (percentage of wins out of total games played). The program then exits.
  10.Random Number Generation:- The code uses the `rand()` function to generate random numbers for simulating the outcome of bets.
  11. Dynamic Memory Allocation:- Dynamic memory allocation is used to create history nodes and duplicate strings for storing operation details.
      

**Explanation of Snake Game** <br>
The code includes various libraries for handling input, time, and console functions. It defines constants for arrow key codes, as well as global variables, structures, and function prototypes.The main function initializes the game and sets up the initial state. It creates the snake, the game board border, and initializes the food. The game loop is handled by the Move function, which continuously updates the snake's position based on user input.The snake can move in four directions: UP, DOWN, LEFT, and RIGHT. It grows in length when it consumes food. The game ends if the snake collides with the border or itself. The player has three lives, and the final score is recorded with the player's name, date, and time in a file called "record.txt."There are various utility functions for handling console output, delay, checking collisions, and updating the score. The game also provides instructions for the player.In summary, it's a simple console-based Snake game with basic features and scoring system

Arrays:bend array: This array of coordinate structures is used to store the coordinates of bends in the snake. As the snake changes direction, bends occur, and their positions need to be remembered to properly draw the snake.body array: Similar to the bend array, the body array is an array of coordinate structures used to store the positions of the snake's body segments. This array is crucial for maintaining the snake's length and checking for collisions.food array: The food array is used to store the coordinates of the food. This information is essential for checking whether the snake has consumed the food, and if so, generating new coordinates for the next food item.Structures:coordinate structure: This structure is used to represent a 2D coordinate on the game board. It includes attributes for the x and y positions, as well as the direction the snake is moving. Instances of this structure are used for the snake's head, bends, body, and food.head structure: The head structure represents the current position and direction of the snake's head. It is of type coordinate and is used to keep track of the snake's movement.
When the snake's head reaches the current food position (head.x == food.x && head.y == food.y), a new food item is generated, and the snake's length is increased.The srand(a) function initializes the random number generator with the current time to ensure a different sequence of random numbers each time the program runs.The rand() % 70 generates a random number between 0 and 69, and similar logic is applied for the y coordinate.If the generated x coordinate is less than or equal to 10, it is adjusted to ensure that the food does not appear too close to the left border. The same adjustment is applied to the y coordinate.If the food's x coordinate is 0, it means that the food needs to be initialized for the first time, so random coordinates are generated as described above.


**Explanation of Connect-4** <br>
The code maintains the core functionality of a Connect 4 game, allowing two players to take turns making moves, checking for wins, and ensuring that invalid moves are not allowed. The implementation uses linked lists within each column to handle the placement of pieces. The `checkWin` function is a placeholder and should be implemented to detect winning conditions based on the rules of Connect 4.

  1. Data Structures:
    Gamecell: Represents an individual cell on the game board. Each `GameCell` has a `value` to store the player's symbol ('X', 'O', or ' ') and a `next` pointer to link to the next cell in the same column.
    GameColumn: Represents a column on the game board, consisting of `GameCell` linked lists. It includes `head` and `tail` pointers to the first and last cells in the column, respectively.
    Connect4game: Represents the game itself and contains an array of `GameColumn` structures to create the game board.
  2. Initialization:
    initializeGame(): Initializes the Connect 4 game board. It allocates memory for the `Connect4Game` structure and initializes each column's `head` and `tail` pointers to `NULL`.
  3. Printing the Game Board:
    printBoard(Connect4Game* game): Prints the current state of the game board. It iterates through each row and column, printing the value of each cell. After each cell is printed, the `head` pointer for that column       is moved to the next cell to ensure correct output formatting.
  4. Valid Move Check:
    isValidMove(Connect4Game* game, int col): Checks if a player's move (column selection) is valid. It verifies that the selected column is within bounds (1-7) and that the column is not already full. It ensures the       player cannot make a move in a full column.
  5. Making a Move:
    makeMove(Connect4Game* game, int col, char player): Adds a player's move to the game board. It allocates a new `GameCell`, sets its `value` to the current player's symbol, and adds it to the end of the column's         linked list. If the column is empty, it updates both the `head` and `tail` pointers.
  6. Checking for a Win:
    checkWin(Connect4Game* game, char player): Placeholder function for checking if the game has been won by the current player. This function can be implemented to check for winning conditions as needed.
  7. Main Game Loop:
   - The game loop allows players to take turns.
   - It prints the board, prompts the current player for a move, validates the move, makes the move, and checks for a win or draw.
   - If a win or draw condition is met, the game loop exits, and the game ends.
  8. Memory Deallocation:
   - After the game is over, the code frees the allocated memory for the cells in each column's linked list and for        
   the`Connect4Game` structure itself.


**Explanation of Tic-Tac-Toe** <br>
This C program implements a 3x3 Tic-Tac-Toe game using structures and arrays. The `TicTacToe` structure represents the game board, and functions are defined to initialize the board, display it, allow players (X and O) to make moves, and check for a winning condition or a draw after each move. The program utilizes a 2D array to store the game board. The main loop of the game prompts players for input in the form of row and column coordinates, validates the input, and updates the board accordingly. The game continues until there is a winner or a draw, and the final board state is displayed. The code demonstrates the use of structures, arrays, loops, conditionals, and user input handling in a simple game scenario.
  1. Header Files and Constants:
     - Includes standard input-output and boolean header files.
     - Defines a constant `SIZE` as 3 for the Tic-Tac-Toe board dimensions.
  2. Structure Definition:
     - Defines a structure `TicTacToe` with a 2D array to represent the game board.
  3. Function to Initialize the Board:
     - `initBoard` initializes each cell of the board to ‘.
  4. Function to Display the Board:
     - `displayBoard` shows the current state of the Tic-Tac-Toe board with row and column separators.
  5.Function to Check for a Win:
     - `checkWin` examines rows, columns, and diagonals to determine if a player has won.
  6.Function to Make a Move:
     - `makeMove` updates the board with the player's move if the cell is empty, otherwise prints an error message.
  7. Main Function:
     - Creates a `TicTacToe` structure for the game board.
     - Initializes the board and sets up variables for the current player, total moves, and game status.
  8. Game Loop:
     - Displays the current board.
     - Takes input from the current player for the row and column.
     - Validates input, updates the board with the player's move.
     - Checks for win or draw conditions and updates the game status.
  9. Final Display:
     - Displays the final state of the Tic-Tac-Toe board.
  10.Return Statement:
     - Indicates successful program execution.


**Contributors ** <br>
  Prajval:-  Casino game, Switch case and ppt
  Ketan:-  Connect4 game , ppt
  Lalith:-  tic-tac-toe
  Manasa:-  Snake Game



