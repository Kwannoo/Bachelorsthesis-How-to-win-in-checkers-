#include <vector>

class minimaxPlayer : public Player{
    public: 
        minimaxPlayer(Checkers* Checkers);
        int evaluate();
        int minimaxAlgorithm(int depth, int &bestmove);
        void doMove();

    private:
        int movesCopy;

};

minimaxPlayer::minimaxPlayer(Checkers* Checkers){
    game = Checkers;
}

int minimaxPlayer::evaluate(){
    int score = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (game->board[i][j] == 'w' || game->board[i][j] == 'W'){
                score += 5;
            }
            if (game->board[i][j] == 'b' || (game->board[i][j] == 'B')){
                score -= 5;
            }
            if (game->board[i][j] == 'W')
                score += 3;

            if (game->board[i][j] == 'B')
                score -= 3;
            
        }
    }
    return score;
}

int minimaxPlayer::minimaxAlgorithm(int depth, int &bestmove){
    calls++;
    std::vector<std::vector<int>> possiblemoves;
    int copyboard[8][8];
    int dummymove;
    bool currentwhoistomove = game->whoistomove;

    possiblemoves = game->availableMoves();

    if (possiblemoves.size() == 0 && game->whoistomove){ //white loses
        return -1000 + moves;
    }

    if (possiblemoves.size() == 0 && !game->whoistomove){ //white loses
        return 1000 - moves;
    }

    if (movesCopy == maximummoves)
        return 0; //draw
    

    if (depth == 0){
        return evaluate();
    }

    std::memcpy (copyboard, game->board, 8*8*sizeof(char));
    if (game->whoistomove){
        int maxValue = -1000000;

        for (size_t i = 0; i < possiblemoves.size(); i++){
            int move = possiblemoves.size()-1-i;
            game->doPossibleMove(possiblemoves[move]);
            // game->doPossibleMove(possiblemoves[i]);
            movesCopy++;
            int eval = minimaxAlgorithm(depth-1, dummymove);
            if (eval > maxValue){
                // bestmove = i;
                bestmove = move;
                maxValue = eval;
            }
            movesCopy--;
            game->whoistomove = currentwhoistomove;
            memcpy(game->board, copyboard, 8*8*sizeof(char));
        }      
        return maxValue; 
    }

    else{
        int minValue = 1000000;
        for (size_t i = 0; i < possiblemoves.size(); i++){
            // game->doPossibleMove(possiblemoves[i]);
            int move = possiblemoves.size()-1-i;
            game->doPossibleMove(possiblemoves[move]);
            movesCopy++;
            int eval = minimaxAlgorithm(depth-1, dummymove);
            if (eval <  minValue){
                // bestmove = i;
                bestmove = move;
                minValue = eval;
            }
            movesCopy--;
            game->whoistomove = currentwhoistomove;
            memcpy(game->board, copyboard, 8*8*sizeof(char));
        }             

        return minValue;
    }
}

void minimaxPlayer::doMove(){
    std::vector<std::vector<int>> possiblemoves;
    bool currentwhoistomove = game->whoistomove;
    int bestmove;
    movesCopy = moves;
    minimaxAlgorithm(depth, bestmove);

    game->whoistomove = currentwhoistomove;
    possiblemoves = game->availableMoves();
    game->doPossibleMove(possiblemoves[bestmove]);
}


