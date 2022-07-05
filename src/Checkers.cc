#include <vector>

class Checkers{
    public:

        bool whoistomove = false;
        char board[8][8];
        int blackpieces, whitepieces; //amount pieces each side

        Checkers();
        ~Checkers();
        void resetboard();
        void printboard();
        bool checkpiece(int i, int j);
        bool validmovewhite(int i, int j, int i2, int j2);
        bool validmoveblack(int i, int j, int i2, int j2);
        void dohumanwhitemove();
        void dohumanblackmove();
        void promote();
        bool validmoveblacknormal(int i, int j, int i2, int j2);
        bool validmovewhitenormal(int i, int j, int i2, int j2);
        bool validmoveking(int i, int j, int i2, int j2);
        void TakeExtraWhite(int i, int j);
        void TakeExtraBlack(int i, int j);
        void TakeExtraKing(int i, int j);
        void TestBoard();
        std::vector<std::vector<int>> PossibleMovesWhite();
        std::vector<std::vector<int>> PossibleMovesWhiteTake();
        void PossibleMovesWhiteTakeMore(int i, int j, std::vector<std::vector<int>> &possiblemoves, std::vector<int> move);
        std::vector<std::vector<int>> PossibleMovesBlack();
        std::vector<std::vector<int>> PossibleMovesBlackTake();
        void PossibleMovesBlackTakeMore(int i, int j, std::vector<std::vector<int>> &possiblemoves, std::vector<int> move);
        bool FirstTakeWhite();
        bool FirstTakeBlack();
        bool FirstTakeKing();
        void doPossibleMove(std::vector<int> possiblemoves);
        int playthegame(int maxgamelength, int depth, bool print,
                        int &nrmoves, int gametypeW, int gametypeB);
        std::vector<std::vector<int>> availableMoves();
        bool HasToTake(int &i, int &j, int &i2, int &j2);
        void doRandomMove();
       
    private:

};

class Player { 
    protected:
        Checkers* game;
    public:
        virtual void doMove(){};
        virtual ~Player(){};
};


//*************************************************************************

Checkers::Checkers(){

}

//*************************************************************************

Checkers::~Checkers(){

}

//*************************************************************************




//*************************************************************************

void Checkers::resetboard(){
    whoistomove = false;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (i < 3){
                if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)){
                    board[i][j] = 'b';
                }
                else{
                    board[i][j] = 'o';
                }
            }
            else if (i > 4){
                if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)){
                    board[i][j] = 'w';
                }
                else{
                    board[i][j] = 'o';
                }    
            }
            else {
                board[i][j] = 'o';
            }
        }
    }
}

//*************************************************************************

void Checkers::printboard(){
    std::cout << "  0 1 2 3 4 5 6 7 " << std::endl;
    for (int i = 0; i < 8; i++){
        std::cout << i;
        for (int j = 0; j < 8; j++){
            std::cout << " " << board[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}

//*************************************************************************

bool Checkers::validmovewhite(int i, int j, int i2, int j2){
     std::cout << "i: " << i << " j: " << j << std::endl;
     std::cout << "i2: " << i2 << " j2: " << j2 << std::endl;


    if (i < 0 && i > 7 && j < 0 && j > 7){
        return false;
    } //out of bounds

    if (i2 < 0 && i2 > 7 && j2 < 0 && j2 > 7){
        return false;
    } //out of bounds

    if (board[i][j] == 'o')
        return false; 

    if (board[i][j] == 'w'){
        return validmovewhitenormal(i, j, i2, j2);
    }
    if (board[i][j] == 'W')
        return validmoveking(i, j, i2, j2);

    return false;

}

//*************************************************************************

//startpos i en j || endpos i en j
bool Checkers::validmovewhitenormal(int i, int j, int i2, int j2){
    if (i < 0 && i > 8 && j < 0 && j > 8) //out of bounds
        return false;

    if ((j - 1 == j2 || j + 1 == j2) && i - 1 == i2){
        if (board[i2][j2] == 'o'){ //return true
            board[i][j] = 'o';
            board[i2][j2] = 'w';
            return true;
        }
        if (board[i2][j2] == 'b' || board[i2][j2] == 'B'){
            if (j - 1 == j2){
                if (board[i-2][j-2] == 'o'){
                    board[i][j] = 'o';
                    board[i-1][j-1] = 'o'; //take black piece
                    board[i-2][j-2] = 'w';
                    std::cout << "black piece is taken" << std::endl;
                    TakeExtraWhite(i-2, j-2);
                    return true;
                }
                    
            }
            if (j + 1 == j2){
                if (board[i-2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i-1][j+1] = 'o'; //take black piece
                    board[i-2][j+2] = 'w';
                    std::cout << "black piece is taken" << std::endl;
                    TakeExtraWhite(i-2, j+2);
                    return true;
                }
            }
        }

    } 
    return false;
}



//*************************************************************************

//startpos i en j || endpos i en j
bool Checkers::validmoveblack(int i, int j, int i2, int j2){

    if (i < 0 && i > 7 && j < 0 && j > 7){
        return false;
    } //out of bounds

    if (i2 < 0 && i2 > 7 && j2 < 0 && j2 > 7){
        return false;
    } //out of bounds

    if (board[i][j] == 'b')
        return validmoveblacknormal(i, j, i2, j2);

    if (board[i][j] == 'B')
        return validmoveking(i, j, i2, j2);

    return false;

}

//*************************************************************************


void Checkers::promote(){
    for (int i = 0; i < 8; i++){
        if (board[0][i] == 'w')
            board[0][i] = 'W';

        if (board[7][i] == 'b')
            board[7][i] = 'B';
    }
}

//*************************************************************************

bool Checkers::validmoveblacknormal(int i, int j, int i2, int j2){
    if ((j - 1 == j2 || j + 1 == j2) && i + 1 == i2){
        if (board[i2][j2] == 'o'){ //return true
            board[i][j] = 'o';
            board[i2][j2] = 'b';
            return true;
        }
        if (board[i2][j2] == 'w' || board[i2][j2] == 'W'){
            if (j - 1 == j2){
                if (board[i+2][j-2] == 'o'){
                    board[i][j] = 'o';
                    board[i+1][j-1] = 'o'; //take white piece
                    board[i+2][j-2] = 'b';
                    TakeExtraBlack(i+2, j-2);
                    return true;
                }
                    
            }
            if (j + 1 == j2){
                if (board[i+2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i+1][j+1] = 'o'; //take black piece
                    board[i+2][j+2] = 'b';
                    TakeExtraBlack(i+2, j+2);
                    return true;
                }
            }
        }

    } 
    return false;
}

//*************************************************************************

bool Checkers::validmoveking(int i, int j, int i2, int j2){
    char Player, Opponent;
    if (!whoistomove){
        Player = 'B';
        Opponent = 'W';
    }
    else{
        Player = 'W';
        Opponent = 'B';
    }
    if ((j - 1 == j2 || j + 1 == j2) && (i + 1 == i2 || i - 1 == i2)){
        if (board[i2][j2] == 'o'){ //go forward or backwards
            board[i][j] = 'o';
            board[i2][j2] = Player;
            return true;
        }
        if (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32){ //take piece
            if (i + 1 == i2 && j - 1 == j2){
                if (board[i+2][j-2] == 'o'){
                    board[i][j] = 'o';
                    board[i+1][j-1] = 'o'; 
                    board[i+2][j-2] = Player;
                    TakeExtraKing(i+2, j-2);
                    return true;
                }
                    
            }
            if (i - 1 == i2 && j - 1 == j2){
                if (board[i-2][j-2] == 'o'){
                    board[i][j] = 'o';
                    board[i-1][j-1] = 'o'; 
                    board[i-2][j-2] = Player;
                    TakeExtraKing(i-2, j-2);
                    return true;
                }
            }
            if (i - 1 == i2 && j + 1 == j2){
                if (board[i-2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i-1][j+1] = 'o'; //take piece
                    board[i-2][j+2] = Player;
                    TakeExtraKing(i-2, j+2);
                    return true;
                }
                    
            }
            if (i + 1 == i2 && j + 1 == j2){
                if (board[i-2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i+1][j+1] = 'o'; //take piece
                    board[i+2][j+2] = Player;
                    TakeExtraKing(i+2, j+2);
                    return true;
                }
                    
            }
        }
    }
    return false;

}

//*************************************************************************

void Checkers::TakeExtraWhite(int i, int j){
    std::string take = "yes";
    int i2, j2;
     
    do {
        // printboard();
        if (((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o') ||
            ((board[i-1][j-1] == 'b' || board[i-1][j-1] == 'B') && board[i-2][j-2] == 'o')){
            std::cout << "Do you want to take another piece? (yes or no): ";
            std::cin >> take;
            if (take == "yes"){
                std::cout << "What is the horizontal coordinate of the taken piece? (0-7): ";
                std::cin >> j2;
                std::cout << "What is the vertical coordinate of the taken piece? (0-7): ";
                std::cin >> i2;
                if (i2 == i-1 && j2 == j-1 && (board[i2][j2] == 'b' || board[i2][j2] == 'B')){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i-2][j-2] = 'w';
                    i -= 2;
                    j -= 2;
                }
                else if (i2 == i-1 && j2 == j+1 && (board[i2][j2] == 'b' || board[i2][j2] == 'B')){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i-2][j+2] = 'w';
                    i -= 2;
                    j += 2;
                }
            }
            else {
                std::cout << "Invalid input try again " << std::endl;
            }

        }
        else{
            break;
        }
    } while (take == "yes" && take != "no");

}

//*************************************************************************

void Checkers::TakeExtraBlack(int i, int j){
    std::string take = "yes";
    int i2, j2;
     
    do {
        if (((board[i+1][j+1] == 'w' || board[i+1][j+1] == 'W') && board[i+2][j+2] == 'o') ||
            ((board[i+1][j-1] == 'w' || board[i+1][j-1] == 'W') && board[i+2][j-2] == 'o')){
            std::cout << "Do you want to take another piece? (yes or no): ";
            std::cin >> take;
            if (take == "yes"){
                std::cout << "What is the horizontal coordinate of the taken piece? (0-7): ";
                std::cin >> j2;
                std::cout << "What is the vertical coordinate of the taken piece? (0-7): ";
                std::cin >> i2;
                if (i2 == i+1 && j2 == j-1 && (board[i2][j2] == 'w' || board[i2][j2] == 'W')){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j-2] = 'b';
                    i += 2;
                    j -= 2;
                }
                else if (i2 == i+1 && j2 == j+1 && (board[i2][j2] == 'w' || board[i2][j2] == 'W')){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j+2] = 'b';
                    i += 2;
                    j += 2;
                }
                else {
                    std::cout << "Invalid input try again " << std::endl;
                }
            }
            else {
                std::cout << "Invalid input try again " << std::endl;
            }

        }
        else{
            break;
        }
    } while (take == "yes" || take != "no");

}

//*************************************************************************

void Checkers::TakeExtraKing(int i, int j){
    char Player, Opponent;
    std::string take = "yes";
    int i2, j2;
    
    if (!whoistomove){
        Player = 'B';
        Opponent = 'W';
    }
    else{
        Player = 'W';
        Opponent = 'B';
    }
    do {
        // printboard();
        if (((board[i+1][j+1] == Opponent || board[i+1][j-1] == Opponent+32) && (board[i+2][j+2] == 'o' || board[i+2][j-2] == 'o'))
          || ((board[i-1][j+1] == Opponent || board[i-1][j-1] == Opponent+32) && (board[i-2][j+2] == 'o' || board[i-2][j-2] == 'o'))){
            std::cout << "Do you want to take another piece? (yes or no): ";
            std::cin >> take;
            if (take == "yes"){
                std::cout << "What is the horizontal coordinate of the taken piece? (0-7): ";
                std::cin >> j2;
                std::cout << "What is the vertical coordinate of the taken piece? (0-7): ";
                std::cin >> i2;
                if (i2 == i-1 && j2 == j-1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i-2][j-2] = Player;
                    i -= 2;
                    j -= 2;
                }
                else if (i2 == i-1 && j2 == j+1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i-2][j+2] = Player;
                    i -= 2;
                    j += 2;
                }
                else if (i2 == i+1 && j2 == j-1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j-2] = Player;
                    i += 2;
                    j -= 2;
                }
                else if (i2 == i+1 && j2 == j+1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j+2] = Player;
                    i += 2;
                    j += 2;
                }
                else {
                    std::cout << "Invalid input try again " << std::endl;
                }
            }
          }
        else{
            break;
        }
    } while (take == "yes" && take != "no");

}

//*************************************************************************

bool Checkers::FirstTakeWhite(){
    //multiple options to take?
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'w'){
                if ((board[i-1][j-1] == 'b' || board[i-1][j-1] == 'B') && board[i-2][j-2] == 'o' ){
                    if (j-2 >= 0 && i-2 >= 0)
                        return true;
                }
                if ((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o' ){
                    if (j+2 < 8 && i-2 >= 0)
                        return true;
                }
            }
        }
    }
    return false;
}

//*************************************************************************

bool Checkers::FirstTakeKing(){
    char Player, Opponent;
    
    if (!whoistomove){
        Player = 'B';
        Opponent = 'W';
    }
    else{
        Player = 'W';
        Opponent = 'B';
    }
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == Player){
                if ((board[i-1][j-1] == Opponent || board[i-1][j-1] == Opponent+32) && board[i-2][j-2] == 'o' ){
                    if (j-2 >= 0 && i-2 >= 0)
                        return true;
                }
                if ((board[i-1][j+1] == Opponent || board[i-1][j+1] == Opponent+32) && board[i-2][j+2] == 'o' ){
                    if (j+2 < 8 && i-2 >= 0)
                        return true;
                }
                if ((board[i+1][j-1] == Opponent || board[i+1][j-1] == Opponent+32) && board[i+2][j-2] == 'o' ){
                    if (j-2 >= 0 && i+2 > 0)
                        return true;
                }
                if ((board[i+1][j+1] == Opponent || board[i+1][j+1] == Opponent+32) && board[i+2][j+2] == 'o' ){
                    if (j+2 < 8 && i+2 < 8)
                        return true;
                }
            }
        }
    }
    return false;
}

bool Checkers::FirstTakeBlack(){
    //multiple options to take?
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'b'){
                if ((board[i+1][j-1] == 'w' || board[i+1][j-1] == 'W') && board[i+2][j-2] == 'o' ){
                    if (j-2 >= 0 && i+2 < 8)
                        return true;
                    
                }
                if ((board[i+1][j+1] == 'w' || board[i+1][j+1] == 'W') && board[i+2][j+2] == 'o' ){
                    if (j+2 < 8 && i+2 < 8)
                        return true;
                    
                }
            }
        }
    }
    return false;
}


// void Checkers::TestBoard(){
//         char board[8][8] = {{'o', 'b', 'o', 'W', 'o', 'W', 'o', 'o'}, {'w', 'o', 'w', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
//          {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'b', 'o', 'o'}, {'o', 'o', 'w', 'o', 'w', 'o', 'o', 'o'},
//          {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'w', 'o', 'o', 'o', 'w', 'o'}}; //white takes

// }

std::vector<std::vector<int>> Checkers::PossibleMovesWhite(){
    std::vector<std::vector<int>> possiblemoves;
    std::vector<int> move;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'w' || board[i][j] == 'W'){
                if (board[i-1][j-1] == 'o'){
                    if (i-1 >= 0 && j-1 >= 0){
                        move = {i,j,i-1,j-1};
                        possiblemoves.push_back(move);
                    }
                }
                if (board[i-1][j+1] == 'o'){
                    if (i-1 >= 0 && j+1 < 8){
                        move = {i,j,i-1,j+1};
                        possiblemoves.push_back(move);
                    }
                }
                if (board[i][j] == 'W'){
                    if (board[i+1][j-1] == 'o'){
                        if (i+1 < 8 && j-1 >= 0){
                            move = {i,j,i+1,j-1};
                            possiblemoves.push_back(move);
                        }
                    }
                    if (board[i+1][j+1] == 'o'){
                        if (i+1 < 8 && j+1 < 8){
                            move = {i,j,i+1,j+1};
                            possiblemoves.push_back(move);
                        }
                    }
                }  
                
            }
        }
    }
    return possiblemoves;
}




std::vector<std::vector<int>> Checkers::PossibleMovesWhiteTake(){
    std::vector<std::vector<int>> possiblemoves;
    std::vector<int> move;
    char Opponent;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 'w' || board[i][j] == 'W'){
                if ((board[i-1][j-1] == 'b' || board[i-1][j-1] == 'B') && board[i-2][j-2] == 'o' ){
                    if (j-2 >= 0 && i-2 >= 0){
                        Opponent = board[i-1][j-1];
                        board[i-1][j-1] = 'o'; //temporary take piece
                        board[i-2][j-2] = board[i][j];
                        board[i][j] = 'o';
                        move = {i, j, i-1, j-1};
                        possiblemoves.push_back(move);
                        PossibleMovesWhiteTakeMore(i-2, j-2, possiblemoves, move);
                        board[i][j] = board[i-2][j-2];
                        board[i-1][j-1]  = Opponent;
                        board[i-2][j-2] = 'o';
                    }
                }
                
                if ((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o' ){
                    if (j+2 < 8 && i-2 >= 0){
                        Opponent = board[i-1][j+1];
                        board[i-1][j+1] = 'o'; //temporary take piece
                        board[i-2][j+2] = board[i][j];
                        board[i][j] = 'o';
                        move = {i, j, i-1, j+1};
                        possiblemoves.push_back(move);
                        PossibleMovesWhiteTakeMore(i-2, j+2, possiblemoves, move);
                        board[i][j] = board[i-2][j+2];
                        board[i-1][j+1]  = Opponent;
                        board[i-2][j+2] = 'o';
                        
                    }
                }
                if (board[i][j] == 'W'){
                    if ((board[i+1][j-1] == 'b' || board[i+1][j-1] == 'B') && board[i+2][j-2] == 'o' ){
                        if (j-2 >= 0 && i+2 < 8){
                            Opponent = board[i+1][j-1];
                            board[i+1][j-1] = 'o'; //temporary take piece
                            board[i+2][j-2] = board[i][j];
                            board[i][j] = 'o';
                            move = {i, j, i+1, j-1};
                            possiblemoves.push_back(move);
                            PossibleMovesWhiteTakeMore(i+2, j-2, possiblemoves, move);
                            board[i][j] = board[i+2][j-2];
                            board[i+1][j-1]  = Opponent;
                            board[i+2][j-2] = 'o';
                        }
                    }
                    if ((board[i+1][j+1] == 'b' || board[i+1][j+1] == 'B') && board[i+2][j+2] == 'o' ){
                        if (j+2 < 8 && i+2 < 8){
                            Opponent = board[i+1][j+1];
                            board[i+1][j+1] = 'o'; //temporary take piece
                            board[i+2][j+2] = board[i][j];
                            board[i][j] = 'o';
                            move = {i, j, i+1, j+1};
                            possiblemoves.push_back(move);
                            PossibleMovesWhiteTakeMore(i+2, j+2, possiblemoves, move);
                            board[i][j] = board[i+2][j+2];
                            board[i+1][j+1]  = Opponent;
                            board[i+2][j+2] = 'o';
                        }
                    }
                }
            }
    }
    return possiblemoves;
}


void Checkers::PossibleMovesWhiteTakeMore(int i, int j, std::vector<std::vector<int>> &possiblemoves, std::vector<int> move){
    char Opponent;
    std::vector<int> currentmove;
    if (board[i][j] == 'w' || board[i][j] == 'W'){
        if (i == 0) //promote
            board[i][j] = 'W'; 
        
        if ((board[i-1][j-1] == 'b' || board[i-1][j-1] == 'B') && board[i-2][j-2] == 'o' ){
            if (j-2 >= 0 && i-2 >= 0){
                Opponent = board[i-1][j-1];
                board[i-1][j-1] = 'o'; //temporary take piece
                board[i-2][j-2] = board[i][j];
                board[i][j] = 'o';
                currentmove = move;
                currentmove.push_back(i);
                currentmove.push_back(j);
                currentmove.push_back(i-1);
                currentmove.push_back(j-1);
                possiblemoves.push_back(currentmove);
                PossibleMovesWhiteTakeMore(i-2, j-2, possiblemoves, currentmove);
                board[i][j] = board[i-2][j-2];
                board[i-1][j-1]  = Opponent;
                board[i-2][j-2] = 'o';
            }
        }
        if ((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o' ){
            if (j+2 < 8 && i-2 >= 0){
                Opponent = board[i-1][j+1];
                board[i-1][j+1] = 'o'; //temporary take piece
                board[i-2][j+2] = board[i][j];
                board[i][j] = 'o';
                currentmove = move;
                currentmove.push_back(i);
                currentmove.push_back(j);
                currentmove.push_back(i-1);
                currentmove.push_back(j+1);
                possiblemoves.push_back(currentmove);
                PossibleMovesWhiteTakeMore(i-2, j+2, possiblemoves, currentmove);
                board[i][j] = board[i-2][j+2];
                board[i-1][j+1]  = Opponent;
                board[i-2][j+2] = 'o';
            }
        }
        if (board[i][j] == 'W'){
            if ((board[i+1][j-1] == 'b' || board[i+1][j-1] == 'B') && board[i+2][j-2] == 'o' ){
                if (j-2 >= 0 && i+2 < 8){
                    Opponent = board[i+1][j-1];
                    board[i+1][j-1] = 'o'; //temporary take piece
                    board[i+2][j-2] = board[i][j];
                    board[i][j] = 'o';
                    currentmove = move;
                    currentmove.push_back(i);
                    currentmove.push_back(j);
                    currentmove.push_back(i+1);
                    currentmove.push_back(j-1);
                    possiblemoves.push_back(currentmove);
                    PossibleMovesWhiteTakeMore(i+2, j-2, possiblemoves, move);
                    board[i][j] = board[i+2][j-2];
                    board[i+1][j-1]  = Opponent;
                    board[i+2][j-2] = 'o';
                }
            }
            if ((board[i+1][j+1] == 'b' || board[i+1][j+1] == 'B') && board[i+2][j+2] == 'o' ){
                if (j+2 < 8 && i+2 < 8){
                    Opponent = board[i+1][j+1];
                    board[i+1][j+1] = 'o'; //temporary take piece
                    board[i+2][j+2] = board[i][j];
                    board[i][j] = 'o';
                    currentmove = move;
                    currentmove.push_back(i);
                    currentmove.push_back(j);
                    currentmove.push_back(i+1);
                    currentmove.push_back(j+1);
                    possiblemoves.push_back(currentmove);
                    PossibleMovesWhiteTakeMore(i+2, j+2, possiblemoves, move);
                    board[i][j] = board[i+2][j+2];
                    board[i+1][j+1]  = Opponent;
                    board[i+2][j+2] = 'o';
                }
            }
        }
    
    }
}

std::vector<std::vector<int>> Checkers::PossibleMovesBlack(){
    std::vector<std::vector<int>> possiblemoves;
    std::vector<int> move;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'b' || board[i][j] == 'B'){
                if (board[i+1][j-1] == 'o'){
                    if (i+1 < 8 && j-1 >= 0){
                        move = {i,j,i+1,j-1};
                        possiblemoves.push_back(move);
                    }
                }
                if (board[i+1][j+1] == 'o'){
                    if (i+1 < 8 && j+1 < 8){
                        move = {i,j,i+1,j+1};
                        possiblemoves.push_back(move);
                    }
                }
                if (board[i][j] == 'B'){
                    if (board[i-1][j-1] == 'o'){
                        if (i-1 >= 0 && j-1 >= 0){
                            move = {i,j,i-1,j-1};
                            possiblemoves.push_back(move);
                        }
                    }
                    if (board[i-1][j+1] == 'o'){
                        if (i-1 >= 0 && j+1 < 8){
                            move = {i,j,i+1,j+1};
                            possiblemoves.push_back(move);
                        }
                    }
                }  
                
            }
        }
    }
    return possiblemoves;
}

std::vector<std::vector<int>> Checkers::PossibleMovesBlackTake(){
    std::vector<std::vector<int>> possiblemoves;
    std::vector<int> move;
    char Opponent;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 'b' || board[i][j] == 'B'){
                if ((board[i+1][j-1] == 'w' || board[i+1][j-1] == 'W') && board[i+2][j-2] == 'o' ){
                    if (j-2 >= 0 && i+2 < 8){
                        Opponent = board[i+1][j-1];
                        board[i+1][j-1] = 'o'; //temporary take piece
                        board[i+2][j-2] = board[i][j];
                        board[i][j] = 'o';
                        move = {i, j, i+1, j-1};
                        possiblemoves.push_back(move);
                        PossibleMovesBlackTakeMore(i+2, j-2, possiblemoves, move);
                        board[i][j] = board[i+2][j-2];
                        board[i+1][j-1]  = Opponent;
                        board[i+2][j-2] = 'o';
                    }
                }
                
                if ((board[i+1][j+1] == 'w' || board[i+1][j+1] == 'W') && board[i+2][j+2] == 'o' ){
                    if (j+2 < 8 && i+2 < 8){
                        Opponent = board[i+1][j+1];
                        board[i+1][j+1] = 'o'; //temporary take piece
                        board[i+2][j+2] = board[i][j];
                        board[i][j] = 'o';
                        move = {i, j, i+1, j+1};
                        possiblemoves.push_back(move);
                        PossibleMovesBlackTakeMore(i+2, j+2, possiblemoves, move);
                        board[i][j] = board[i+2][j+2];
                        board[i+1][j+1]  = Opponent;
                        board[i+2][j+2] = 'o';
                        
                    }
                }
                if (board[i][j] == 'B'){
                    
                    if ((board[i-1][j+1] == 'w' || board[i-1][j+1] == 'W') && board[i-2][j+2] == 'o' ){
                        if (j+2 < 8 && i-2 >= 0){
                            Opponent = board[i-1][j+1];
                            board[i-1][j+1] = 'o'; //temporary take piece
                            board[i-2][j+2] = board[i][j];
                            board[i][j] = 'o';
                            move = {i, j, i-1, j+1};
                            possiblemoves.push_back(move);
                            PossibleMovesBlackTakeMore(i-2, j+2, possiblemoves, move);
                            board[i][j] = board[i-2][j+2];
                            board[i-1][j+1]  = Opponent;
                            board[i-2][j+2] = 'o';
                        }
                    }
                    if ((board[i-1][j-1] == 'w' || board[i-1][j-1] == 'W') && board[i-2][j-2] == 'o' ){
                        if (j-2 >= 0 && i-2 >= 0){
                            Opponent = board[i-1][j-1];
                            board[i-1][j-1] = 'o'; //temporary take piece
                            board[i-2][j-2] = board[i][j];
                            board[i][j] = 'o';
                            move = {i, j, i-1, j-1};
                            possiblemoves.push_back(move);
                            PossibleMovesBlackTakeMore(i-2, j-2, possiblemoves, move);
                            board[i][j] = board[i-2][j-2];
                            board[i-1][j-1]  = Opponent;
                            board[i-2][j-2] = 'o';
                        }
                    }
                }
            }
    }
    return possiblemoves;
}


void Checkers::PossibleMovesBlackTakeMore(int i, int j, std::vector<std::vector<int>> &possiblemoves, std::vector<int> move){
    char Opponent;
    std::vector<int> currentmove;
    if (board[i][j] == 'b' || board[i][j] == 'B'){
        if (i == 7) //promote
            board[i][j] = 'B'; 
        
        if ((board[i+1][j-1] == 'w' || board[i+1][j-1] == 'W') && board[i+2][j-2] == 'o' ){
            if (j-2 >= 0 && i+2 < 8){
                Opponent = board[i+1][j-1];
                board[i+1][j-1] = 'o'; //temporary take piece
                board[i+2][j-2] = board[i][j];
                board[i][j] = 'o';
                currentmove = move;
                currentmove.push_back(i);
                currentmove.push_back(j);
                currentmove.push_back(i+1);
                currentmove.push_back(j-1);
                possiblemoves.push_back(currentmove);
                PossibleMovesBlackTakeMore(i+2, j-2, possiblemoves, currentmove);
                board[i][j] = board[i+2][j-2];
                board[i+1][j-1]  = Opponent;
                board[i+2][j-2] = 'o';
            }
        }
        if ((board[i+1][j+1] == 'w' || board[i+1][j+1] == 'W') && board[i+2][j+2] == 'o' ){
            if (j+2 < 8 && i+2 < 8){
                Opponent = board[i+1][j+1];
                board[i+1][j+1] = 'o'; //temporary take piece
                board[i+2][j+2] = board[i][j];
                board[i][j] = 'o';
                currentmove = move;
                currentmove.push_back(i);
                currentmove.push_back(j);
                currentmove.push_back(i+1);
                currentmove.push_back(j+1);
                possiblemoves.push_back(currentmove);
                PossibleMovesBlackTakeMore(i+2, j+2, possiblemoves, currentmove);
                board[i][j] = board[i+2][j+2];
                board[i+1][j+1]  = Opponent;
                board[i+2][j+2] = 'o';
            }
        }
        if (board[i][j] == 'B'){
            if ((board[i-1][j-1] == 'w' || board[i-1][j-1] == 'W') && board[i-2][j-2] == 'o' ){
                if (j-2 >= 0 && i-2 >= 0){
                    Opponent = board[i-1][j-1];
                    board[i-1][j-1] = 'o'; //temporary take piece
                    board[i-2][j-2] = board[i][j];
                    board[i][j] = 'o';
                    currentmove = move;
                    currentmove.push_back(i);
                    currentmove.push_back(j);
                    currentmove.push_back(i-1);
                    currentmove.push_back(j-1);
                    possiblemoves.push_back(currentmove);
                    PossibleMovesBlackTakeMore(i-2, j-2, possiblemoves, move);
                    board[i][j] = board[i-2][j-2];
                    board[i-1][j-1]  = Opponent;
                    board[i-2][j-2] = 'o';
                }
            }
            if ((board[i-1][j+1] == 'w' || board[i-1][j+1] == 'W') && board[i-2][j+2] == 'o' ){
                if (j+2 < 8 && i-2 >= 0){
                    Opponent = board[i-1][j+1];
                    board[i-1][j+1] = 'o'; //temporary take piece
                    board[i-2][j+2] = board[i][j];
                    board[i][j] = 'o';
                    currentmove = move;
                    currentmove.push_back(i);
                    currentmove.push_back(j);
                    currentmove.push_back(i-1);
                    currentmove.push_back(j+1);
                    possiblemoves.push_back(currentmove);
                    PossibleMovesBlackTakeMore(i-2, j+2, possiblemoves, move);
                    board[i][j] = board[i-2][j+2];
                    board[i-1][j+1]  = Opponent;
                    board[i-2][j+2] = 'o';
                }
            }
        }
    
    }
}

//*************************************************************************

void Checkers::doPossibleMove(std::vector<int>possiblemoves){

    do{
        // std::cout << "possiblemove bs" << std::endl;
        if (board[possiblemoves[2]][possiblemoves[3]] != 'o'){
            if (possiblemoves[0]+1 == possiblemoves[2] && possiblemoves[1]+1 == possiblemoves[3]) { //take bottom right
                board[possiblemoves[2]][possiblemoves[3]] = 'o';
                board[possiblemoves[2]+1][possiblemoves[3]+1] = board[possiblemoves[0]][possiblemoves[1]];
                // std::cout << "bottom right" << std::endl;

            }
            else if (possiblemoves[0]+1 == possiblemoves[2] && possiblemoves[1]-1 == possiblemoves[3]) { //take bottom left
                board[possiblemoves[2]][possiblemoves[3]] = 'o';
                board[possiblemoves[2]+1][possiblemoves[3]-1] = board[possiblemoves[0]][possiblemoves[1]];
                // std::cout << "bottom left" << std::endl;
            }
            else if (possiblemoves[0]-1 == possiblemoves[2] && possiblemoves[1]+1 == possiblemoves[3]) { //take top right 
                board[possiblemoves[2]][possiblemoves[3]] = 'o';
                board[possiblemoves[2]-1][possiblemoves[3]+1] = board[possiblemoves[0]][possiblemoves[1]];
                // std::cout << "top right" << std::endl;
            }
            else if (possiblemoves[0]-1 == possiblemoves[2] && possiblemoves[1]-1 == possiblemoves[3]) { //take top left
                board[possiblemoves[2]][possiblemoves[3]] = 'o';
                board[possiblemoves[2]-1][possiblemoves[3]-1] = board[possiblemoves[0]][possiblemoves[1]];
                // std::cout << "top left" << std::endl;
            }
        }
        else { //no takes just move
            board[possiblemoves[2]][possiblemoves[3]] = board[possiblemoves[0]][possiblemoves[1]];
            // if(possiblemoves[2] == 7 &&)
            // std::cout << "nothing" << std::endl;
        }
        board[possiblemoves[0]][possiblemoves[1]] = 'o';
        promote();
        possiblemoves.erase(possiblemoves.begin(), possiblemoves.begin()+4);
    } while (!possiblemoves.empty());

    whoistomove = !whoistomove;
    
}



bool Checkers::HasToTake(int &i, int &j, int &i2, int &j2){
    char Player;
    char Opponent;
    if (!whoistomove){
        Player = 'B';
        Opponent = 'W';
    }
    else{
        Player = 'W';
        Opponent = 'B';
    }
    std::cout << "Which piece would you like to move?" << std::endl;
    std::cout << "Fill in horizontal coordinate (0-7): ";
    std::cin >> j;
    std::cout << "Fill in vertical coordinate (0-7): ";
    std::cin >> i;

    std::cout << "Where do you want your piece to move?" << std::endl;
    std::cout << "Fill in horizontal coordinate (0-7): ";
    std::cin >> j2;
    std::cout << "Fill in vertical coordinate (0-7): ";
    std::cin >> i2;

    if (whoistomove){
        if ((j - 1 == j2 || j + 1 == j2) && i - 1 == i2){
            if (board[i2][j2] == 'b'){
                if (j - 1 == j2){
                    if (board[i-2][j-2] == 'o'){
                        return true;
                    }
                        
                }
                if (j + 1 == j2){
                    if (board[i-2][j+2] == 'o'){
                        return true;
                    }
                }
            }
        }
    }
    else {
        if ((j - 1 == j2 || j + 1 == j2) && i + 1 == i2){
            if (board[i2][j2] == 'w'){
                if (j - 1 == j2){
                    if (board[i+2][j-2] == 'o'){
                        return true;
                    }
                        
                }
                if (j + 1 == j2){
                    if (board[i+2][j+2] == 'o'){
                        return true;
                    }
                }
            }
        }
    }
    if ((j - 1 == j2 || j + 1 == j2) && (i + 1 == i2 || i - 1 == i2)){
            if (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32){ //take piece
                if (i + 1 == i2 && j - 1 == j2){
                    if (board[i+2][j-2] == 'o')
                        return true; 
                }
                if (i - 1 == i2 && j - 1 == j2){
                    if (board[i-2][j-2] == 'o')
                        return true;
                }
                if (i - 1 == i2 && j + 1 == j2){
                    if (board[i-2][j+2] == 'o')
                        return true;
                }
                if (i + 1 == i2 && j + 1 == j2){
                    if (board[i+2][j+2] == 'o')
                        return true;
                }
            }
        }
    return false;
}


std::vector<std::vector<int>> Checkers::availableMoves(){
    std::vector<std::vector<int>> possiblemoves;
    if (whoistomove){
        if (FirstTakeWhite() || FirstTakeKing()){
            possiblemoves = PossibleMovesWhiteTake();
        }
        else {
            possiblemoves = PossibleMovesWhite();

        }
    }
    else{
        if (FirstTakeBlack() || FirstTakeKing()){
            possiblemoves = PossibleMovesBlackTake();
        }
        else {
            possiblemoves = PossibleMovesBlack();

        }
    }
    return possiblemoves;
}

void Checkers::doRandomMove(){
    std::vector<std::vector<int>> possiblemoves;
    possiblemoves = availableMoves();

    size_t random = rand() % possiblemoves.size();

    doPossibleMove(possiblemoves[random]);
    //printboard();
}


//https://github.com/kurebasu/Dots-and-Boxes/blob/master/src/MCTSPlayer.cc