# Bachelorsthesis-How-to-win-in-checkers-

Checkers is a board game played by two players, and the objective of the game is to capture all the opponent's pieces. This thesis will compare two algorithms, minimax and Monte Carlo Tree Search (MCTS), and see which algorithm is able to play the game better. This thesis contains information about the game Checkers itself as well as the algorithms. This also contains a short explanation of how the code, for running the experiments, is constructed. In order to determine which one of the algorithms performs the best, both algorithms will be optimized first. The minimax will be optimized based on the king value relatively to a normal piece and the positional structure. Also, a comparison of function calls between the regular minimax and minimax $\alpha \beta$. An attempt has been made to optimize the efficiency of the minimax $\alpha \beta$. For the MCTS, the constant value C in the UCB1 formula has been optimized to the value 0.3. Lastly, the two algorithms play against each other by having the MCTS algorithm having 100-500 playouts play against minimax $\alpha \beta$ with a depth 2-4. MCTS resulted in drawing and losing many games against the minimax player. This is probably due to the game setup or the amount of playouts the MCTS algorithm has. So for further research, the suggestion is to test the comparison on a variation of Checkers or rewrite/optimize the code in order to make the MCTS play with more playouts.

## How to Run the Files

To run the files, follow these steps:

1. Enter the following command in the command line to create an object from the makefile:

2. After successfully creating the object, you can execute the program using the following command: ./Checkers <numberOfGames> <gIterations> <depth> <print[0/1]> <playerMode1[0-3]> <playerMode2[0-3]> <seed>

Replace the placeholders with the desired parameters:

- `numberOfGames`: Number of games to be played.
- `gIterations`: Playouts of MCTS (Monte Carlo Tree Search).
- `depth`: Depth of minimax.
- `print[0/1]`: 
  - `1`: Print every game.
  - `0`: Do not print.
- `playerMode1` and `playerMode2`:
  - `0`: Random Player.
  - `1`: Minimax Player.
  - `2`: Human Player.
  - `3`: MCTS Player.
- `seed`: A seed value if needed.

For example, to run a game with 1000 iterations of MCTS, a depth of 3 for minimax, printing enabled, both players as Minimax Players, and a seed of 123:

./Checkers 1 1000 3 1 1 1 123

Disclaimer: The code has not been cleaned so comments still need to be added and code can be optimized
