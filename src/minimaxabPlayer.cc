#include <vector>

class minimaxabPlayer : public Player{
    public: 
        minimaxabPlayer(Checkers* Checkers);
        int evaluate();
        int minimaxAlgorithmAlphaBeta(int depth, int &bestmove, int alpha, int beta);
        void doMove();

    private:
        int movesCopy;

};

minimaxabPlayer::minimaxabPlayer(Checkers* Checkers){
    game = Checkers;
}

int minimaxabPlayer::evaluate(){
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

int minimaxabPlayer::minimaxAlgorithmAlphaBeta(int depth, int &bestmove, int alpha, int beta){
    calls2++;
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
            // game->doPossibleMove(possiblemoves[i]);
            int move = possiblemoves.size()-1-i;
            game->doPossibleMove(possiblemoves[move]);
            movesCopy++;
            int eval = minimaxAlgorithmAlphaBeta(depth-1, dummymove, alpha, beta);
            if (eval > maxValue){
                maxValue = eval;
            }
            if (eval > alpha){
                alpha = eval;
                // bestmove = i;
                bestmove = move;
            }
            if (beta <= alpha){
                movesCopy--;
                game->whoistomove = currentwhoistomove;
                memcpy(game->board, copyboard, 8*8*sizeof(char));
                break;
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
            int eval = minimaxAlgorithmAlphaBeta(depth-1, dummymove, alpha, beta);
            if (eval < minValue){
                minValue = eval;
            }
            if (eval < beta){
                beta = eval;
                // bestmove = i;
                bestmove = move;
            }
            if (beta <= alpha){
                movesCopy--;
                game->whoistomove = currentwhoistomove;
                memcpy(game->board, copyboard, 8*8*sizeof(char));
                break;
            }
            movesCopy--;
            game->whoistomove = currentwhoistomove;
            memcpy(game->board, copyboard, 8*8*sizeof(char));
        }             

        return minValue;
    }
}

void minimaxabPlayer::doMove(){
    std::vector<std::vector<int>> possiblemoves;
    bool currentwhoistomove = game->whoistomove;
    

    int bestmove;
    movesCopy = moves;
    minimaxAlgorithmAlphaBeta(depth, bestmove, -20000000, 20000000);

    game->whoistomove = currentwhoistomove;
    possiblemoves = game->availableMoves();
    game->doPossibleMove(possiblemoves[bestmove]);
}

