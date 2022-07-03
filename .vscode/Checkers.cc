#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>



//*************************************************************************

Checkers::Checkers(){

}

//*************************************************************************

Checkers::~Checkers(){

}

//*************************************************************************

void Checkers::resetboard(){
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


    if (i < 0 && i > 8 && j < 0 && j > 8){
        return false;
    } //out of bounds

    if (i2 < 0 && i2 > 8 && j2 < 0 && j2 > 8){
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
     std::cout << "i: " << i << " j: " << j << std::endl;
     std::cout << "i2: " << i2 << " j2: " << j2 << std::endl;


    if (i < 0 && i > 8 && j < 0 && j > 8){
        return false;
    } //out of bounds

    if (i2 < 0 && i2 > 8 && j2 < 0 && j2 > 8){
        return false;
    } //out of bounds

    if (board[i][j] == 'b')
        return validmoveblacknormal(i, j, i2, j2);

    if (board[i][j] == 'B')
        return validmoveking(i, j, i2, j2);

    return false;

}

//*************************************************************************

void Checkers::dohumanwhitemove(){
    bool valid = false;
    bool takemove = false;
    int i,j;
    int i2, j2;
    std::cout << "White to move: " << std::endl;
    do{
        printboard();
        if (FirstTakeWhite() || FirstTakeKing()){
            do{
                if (HasToTake(i, j, i2, j2))
                    takemove = true;
                else{
                    std::cout << "You have to take a piece!" << std::endl;
                    printboard();
                }
            } while(!takemove);
            if (validmovewhite(i, j, i2, j2)){ //if statement not needed but test
                valid = true;
                //board[i][j] = 'o';
            }
        }
        // else if (FirstTakeKing(i,j,i2,j2)){
        //     if (validmovewhite(i, j, i2, j2)){
        //         valid = true;
        //        // board[i][j] = 'o';
        //     }
        // }
        else{
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
            if (validmovewhite(i, j, i2, j2)){
                valid = true;
               // board[i][j] = 'o';
            }
            
            else
                std::cout << "Invalid move please enter correctly\n" << std::endl;
        }
            

    } while(!valid);
    
}


//*************************************************************************

void Checkers::dohumanblackmove(){
    bool valid = false;
    bool takemove = false;
    int i,j;
    int i2, j2;

    std::cout << "Black to move: " << std::endl;

    do {
        printboard();
        if (FirstTakeBlack() || FirstTakeKing()){
            do{
                if (HasToTake(i, j, i2, j2))
                    takemove = true;
                else{
                    std::cout << "You have to take a piece!" << std::endl;
                    printboard();
                }
            } while(!takemove);
            if (validmoveblack(i, j, i2, j2)){ //if statement not needed but test
                valid = true;
                //board[i][j] = 'o';
            }
        }
        // else if (FirstTakeKing(i,j,i2,j2)){
        //     if (validmoveblack(i, j, i2, j2)){
        //         valid = true;
        //         //board[i][j] = 'o';
        //     }
        // }
        else{
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
            if (validmoveblack(i, j, i2, j2)){
                valid = true;
                //board[i][j] = 'o';
            }
            else{
                std::cout << "Invalid move please enter correctly\n" << std::endl;
            }
        }
    } while(!valid);
    
}

// void Checkers::playthegame(){
//     while (blackpieces != 0 || whitepieces != 0){
//         if (!whoistomove){
//             dohumanblackmove();
//         }
//         else{
//             dohumanwhitemove();
//         }
//         whoistomove = !whoistomove;
//         promote();
//         //printboard();
//     }

//     std::cout << "game is done" << std::endl;
// }


void Checkers::promote(){
    for (int i = 0; i < 8; i++){
        if (board[0][i] == 'w')
            board[0][i] = 'W';

        if (board[7][i] == 'b')
            board[7][i] = 'B';
    }
}

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

void Checkers::TakeExtraBlack(int i, int j){
    std::string take = "yes";
    int i2, j2;
     
    do {
        // printboard();
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
          || (board[i-1][j+1] == Opponent || board[i-1][j-1] == Opponent+32) && (board[i-2][j+2] == 'o' || board[i-2][j-2] == 'o')){
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

bool Checkers::FirstTakeWhite(){
    //multiple options to take?
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'w'){
                if ((board[i-1][j-1] == 'b' || board[i-1][j-1] == 'B') && board[i-2][j-2] == 'o' ){
                    if (j-2 >= 0 && i-2 >= 0){
                        // std::cout << "first take gevonden white bool" << std::endl;
                        return true;
                    }
                }
                else if ((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o' ){
                    if (j+2 < 8 && i-2 >= 0){
                        // std::cout << "first take gevonden white bool" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

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
                    if (j-2 >= 0 && i-2 >= 0){
                        // std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
                }
                else if ((board[i-1][j+1] == Opponent || board[i-1][j+1] == Opponent+32) && board[i-2][j+2] == 'o' ){
                    if (j+2 < 8 && i-2 >= 0){
                        // std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
                }
                else if ((board[i+1][j-1] == Opponent || board[i+1][j-1] == Opponent+32) && board[i+2][j-2] == 'o' ){
                    if (j-2 >= 0 && i+2 > 0){
                        // std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
                }
                else if ((board[i+1][j+1] == Opponent || board[i+1][j+1] == Opponent+32) && board[i+2][j+2] == 'o' ){
                    if (j+2 < 8 && i+2 < 8){
                        // std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
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
                    if (j-2 >= 0 && i+2 < 8){
                        // std::cout << "first take gevonden black 1" << std::endl;
                        return true;
                    }
                }
                else if ((board[i+1][j+1] == 'w' || board[i+1][j+1] == 'W') && board[i+2][j+2] == 'o' ){
                    if (j+2 < 8 && i+2 < 8){
                        // std::cout << "first take gevonden black 2" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void Checkers::TestBoard(){
        // char board[8][8] = {{'o', 'b', 'o', 'b', 'o', 'b', 'o', 'b'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o'},
        //  {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'b', 'o', 'b', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
        //  {'o', 'o', 'o', 'o', 'o', 'b', 'o', 'o'}, {'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o'}}; white takes

        // char board[8][8] = {{'o', 'o', 'o', 'b', 'o', 'o', 'o', 'b'}, {'o', 'o', 'W', 'o', 'w', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
        //  {'w', 'o', 'w', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
        //  {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}};

}

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
                        if (i+1 < 8 && j-1 <= 0){
                            move = {i,j,i+1,j-1};
                            possiblemoves.push_back(move);
                        }
                    }
                    if (board[i+1][j+1] == 'o'){
                        if (i+1 <= 8 && j+1 < 8){
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

int Checkers::MinimaxAlgorithm(int depth, int &bestmove){
    std::vector<std::vector<int>> possiblemoves;
    int copyboard[8][8];
    int dummymove;
    bool currentwhoistomove = whoistomove;
    // std::cout << "do minimax" << std::endl;


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
            // std::cout << "first take is true" << std::endl;

            possiblemoves = PossibleMovesBlackTake();
        }
        else {
            possiblemoves = PossibleMovesBlack();

        }
    }
    
    if (possiblemoves.size() == 0 && whoistomove){ //white loses
        return -1000;
    }

    if (possiblemoves.size() == 0 && !whoistomove){ //white loses
        return 1000;
    }

    if (depth == 0){
        return evaluate();
    }

        // for (size_t i = 0; i < possiblemoves.size(); i++){
        //     std::cout << "possiblemoves: ";
        //         for (size_t j = 0; j < possiblemoves[i].size(); j++){
        //             std::cout << " " << possiblemoves[i][j];
        //         }
        //     std::cout << std::endl;
        // }

    std::memcpy (copyboard, board, 8*8*sizeof(char));
    if (whoistomove){
        int maxValue = -1000000;

        for (size_t i = 0; i < possiblemoves.size(); i++){
            DoPossibleMove(possiblemoves[i]);
            int eval = MinimaxAlgorithm(depth-1, dummymove);
            if (eval > maxValue){
                bestmove = i;
                maxValue = eval;
            }
            whoistomove = currentwhoistomove;
            memcpy(board, copyboard, 8*8*sizeof(char));
        }      
        return maxValue; 
    }

    else{
        int minValue = 1000000;
        for (size_t i = 0; i < possiblemoves.size(); i++){
            DoPossibleMove(possiblemoves[i]);
            int eval = MinimaxAlgorithm(depth-1, dummymove);
            if (eval <  minValue){
                bestmove = i;
                minValue = eval;
            }
            whoistomove = currentwhoistomove;
            memcpy(board, copyboard, 8*8*sizeof(char));
        }             

        return minValue;
    }
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
                            board[i][j] = board[i+2][j-2];
                            board[i-1][j+1]  = Opponent;
                            board[i-2][j+2] = 'o';
                        }
                    }
                    if ((board[i-1][j-1] == 'w' || board[i-1][j-1] == 'W') && board[i-2][j-2] == 'o' ){
                        std::cout << "do this shit" << std::endl;
                        if (j-2 >= 0 && i-2 >= 0){
                            Opponent = board[i-1][j-1];
                            board[i-1][j-1] = 'o'; //temporary take piece
                            board[i-2][j-2] = board[i][j];
                            board[i][j] = 'o';
                            move = {i, j, i-1, j-1};
                            possiblemoves.push_back(move);
                            std::cout << "do this next??" << std::endl;
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

void Checkers::DoPossibleMove(std::vector<int>possiblemoves){

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
        possiblemoves.erase(possiblemoves.begin(), possiblemoves.begin()+4);
    } while (!possiblemoves.empty());

    whoistomove = !whoistomove;
}



bool Checkers::HasToTake(int &i, int &j, int &i2, int &j2){
    char Player, Opponent;
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

//*************************************************************************

int Checkers::evaluate(){
    int score = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'w' || board[i][j] == 'W'){
                score += 5;
            }
            if (board[i][j] == 'b' || board[i][j] == 'B'){
                score -= 5;
            }
        }
    }
    return score;
}

void Checkers::DoMinimaxMove(){
    std::vector<std::vector<int>> possiblemoves;
    bool currentwhoistomove = whoistomove;
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
            std::cout << "first take is true" << std::endl;

            possiblemoves = PossibleMovesBlackTake();
        }
        else {
            possiblemoves = PossibleMovesBlack();

        }
    }

    int bestmove;
    MinimaxAlgorithm(3, bestmove);

    std::cout << "best move: " << bestmove << std::endl;
    whoistomove = currentwhoistomove;
   

    DoPossibleMove(possiblemoves[bestmove]);
    // printboard();
}

void Checkers::DoRandomMove(){
    std::vector<std::vector<int>> possiblemoves;
    bool currentwhoistomove = whoistomove;
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
            // std::cout << "first take is true" << std::endl;

            possiblemoves = PossibleMovesBlackTake();
        }
        else {
            possiblemoves = PossibleMovesBlack();

        }
    }
   
    size_t random = rand() % possiblemoves.size();
    DoPossibleMove(possiblemoves[random]);
}

//*******************************************************************
//START MCTS

Node::Node(){
	wins = losses = ties = 0;
	isRoot = true;
	parent = NULL;
	nodeNumber = 0;
	gNumberOfNodes = 1;
}

Node::Node(Node* creator){
	isRoot = false;
	parent = creator;
	wins = losses = ties = 0;
	nodeNumber = gNumberOfNodes;
	gNumberOfNodes++;
}

Node::~Node(){
	for(Node* node : children){
		delete node;
	}
}


void Node::cleanTree(){
	for(Node* node : children){
		std::cout << "hier 4" << std::endl;
		delete node;
		node = NULL;
		// std::cout << "hier 5" << std::endl;
	}
    std::cout << "after for loop" << std::endl;
	children.clear();
	wins = losses = ties = 0;
	gNumberOfNodes = 1;
}

bool Node::isLeafNode(){
	return !(bool)(children.size());
}

int Node::maxChild(bool justSelection){
	double maxValue = INT_MIN;
	double currentValue = INT_MIN;
	int move = 0;
	int bestMove = INT_MIN;
	int visits = 0;
	// if(this->isRoot){
		// std::cout << "begin maxchild" << std::endl;
		// std::cout << "#children = " << children.size() << std::endl;
		// printTree();
	// }
	for(Node* node : children){
        if (justSelection)
            currentValue = node->calcUCB1Value();
            std::cout << "currentValue: " << currentValue << std::endl;
		// if(gMove == 0 || justSelection){//UCB1
		// 	currentValue = node->calcUCB1Value();
		// }
		// else if(gMove == 1){//MAX CHILD
		// 	visits = node->getVisits();
		// 	if (visits == 0){
		// 		visits = 1; //make sure we don't divide by 0
		// 	}
		// 	currentValue = double((double)(node->getWins())/(double)(visits));
		// }
		// else if(gMove == 2){//ROBUST CHILD
		// 	currentValue = node->getVisits();
		// }
		if(currentValue > maxValue){
			bestMove = move;
			maxValue = currentValue;
		}
		++move;
	}
	// std::cout << std::endl;
	return bestMove;
}

void Node::printAllChild(){
	double currentValue = INT_MIN;
	int i = 0;
	int visits = 0;
    int gMove = 0;
	for(Node* node : children){
		if(gMove == 0){//UCB1
			currentValue = node->calcUCB1Value();
		}
		else if(gMove == 1){//MAX CHILD
			visits = node->getVisits();
			if (visits == 0){
				visits = 1; //make sure we don't divide by 0
			}
			currentValue = (double)(node->getWins())/(double)(visits);
		}
		else if(gMove == 2){//ROBUST CHILD
			currentValue = node->getVisits();
		}
		std::cout << "currentValue for child " << i++ << " : " << currentValue <<std::endl;
	}
}

double Node::calcUCB1Value(){
	double C = 0.4; //constant value
	int Wi = wins;
	double ni = (double)getVisits();
	int Ni = 0;
	double UCB1 = 0;
	if(parent != NULL) //which it should never be...
		Ni = parent->getVisits();

  //for calculation purposes and avoiding dividing by 0
  if(ni == 0){
		ni = 0.5;
	}

    std::cout << "Wi" << Wi << std::endl;
    std::cout << "ni" << ni << std::endl;

    std::cout << "Ni" << Ni << std::endl;


	UCB1 = (Wi/ni) + (C * sqrt( (log(Ni) / ni) ));

	return UCB1;
}



void Node::updateValue(){
	int oldWins 	= wins;
	int oldLosses 	= losses;
	int oldTies 	= ties;

	wins = losses = ties = 0;

	for(Node* node : children){
		if(node != NULL){
			wins 	+= node->getWins();
			losses 	+= node->getLosses();
			ties 	+= node->getTies();
		}
	}

	if(parent != NULL){
		parent->backPropagate((wins - oldWins), (losses - oldLosses), (ties - oldTies)); //Give the difference in score back to parent
	}
}

void Node::backPropagate(int wins1, int losses1, int ties1){
	wins 	+= wins1;
	losses 	+= losses1;
	ties 	+= ties1;
	if(parent != NULL){
		parent->backPropagate(wins1, losses1, ties1);
	}
}

bool Node::isConsistent(){
	int cWins = 0;
	int cLosses = 0;
	int cTies = 0;

	for(Node* node : children){
        std::cout << "go past children" << std::endl;
		if(node != NULL){
            // std::cout << "cWins: " << node->getWins() << std::endl;
            // std::cout << "cLosses: " << node->getLosses() << std::endl;
            // std::cout << "cTies: " << node->getTies() << std::endl;
            // std::cout << "------------------------------------" << std::endl;
			cWins += node->getWins();
			cLosses += node->getLosses();
			cTies += node->getTies();
		}
	}


    std::cout << "Wins: " << wins << std::endl;
    std::cout << "Losses: " << losses << std::endl;
    std::cout << "Ties: " << ties << std::endl;

	//Check if this node is inconsistent with children
	if(cWins != wins || cLosses != losses || cTies != ties){
        std::cout << "this goes wrong" << std::endl;
		return false;
	}

	//Check if this node is inconsistent with children (might be off by 2 but eh)
	if(!((cWins == wins || cWins == wins +1)
   	&&(cLosses == losses || cLosses == losses +1)
		&&(cTies == ties || cTies == ties + 1))){
			return false;
		}
	if(!(getVisits() == cWins + cLosses + cTies + 1)){
		std::cout << nodeNumber << " is the problemo" << std::endl;
		std::cout << "cwins = " << cWins << " closses = " << cLosses << " cTies = " << cTies << std::endl;
		std::cout << "getvisits() = " << getVisits() << std::endl;
		std::cout << "getvisits = niet alles children +1" << std::endl;
		return false;
	}

	else{ //check if children are consistent
		for(Node* node : children){
			if(node != NULL){
				if(!(node->isConsistent())){
					return false;
				}
			}
		}
	 }

	return true;

}

void Node::printTree(bool first){
	Node* cParent = parent;
	if(first){
		std::cout << "start of print tree:" << std::endl;
		std::cout << "digraph test{" << std::endl;
	}

	//print line for the node itself
	// if(getVisits() > 0){ //if it is not empty
		std::cout << nodeNumber << " [label=\"" << wins << "/" << losses << "/" << ties << "\" color=black, "
							<< "fontcolor=black, fontsize=12, shape=circle]" << std::endl;
		//print line for connection with parent:
		if(parent!= NULL){
			std::cout << parent->nodeNumber << " -> " << nodeNumber << ";" << std::endl;
		}
	// }


	// std::cout << "myNumber: " << nodeNumber <<std::endl;
	//
	// while(cParent != NULL){
	// 	std::cout << " child of: " << cParent->nodeNumber;
	// 	cParent = cParent->parent;
	// }
	//
	// std::cout << std::endl << "wins :" << wins << " losses: " << losses << " ties: " << ties << std::endl;
	//
	// std::cout << std::endl;

	for (Node* node : children){
		node->printTree(false);
	}


	if(first){
		std::cout << "}" << std::endl;
		std::cout << "end of print tree:" << std::endl;
	}

}

void Node::printRoot(bool first){
	Node* cParent = parent;
	if(first){
		std::cout << "start of print tree:" << std::endl;
		std::cout << "digraph test{" << std::endl;
	}

	//print line for the node itself
	if(getVisits() > 0){ //if it is not empty
		std::cout << nodeNumber << " [label=\"" << wins << "/" << losses << "/" << ties << "\" color=black, "
							<< "fontcolor=black, fontsize=12, shape=circle]" << std::endl;
		//print line for connection with parent:
		if(parent!= NULL){
			std::cout << parent->nodeNumber << " -> " << nodeNumber << ";" << std::endl;
		}
	}


	// std::cout << "myNumber: " << nodeNumber <<std::endl;
	//
	// while(cParent != NULL){
	// 	std::cout << " child of: " << cParent->nodeNumber;
	// 	cParent = cParent->parent;
	// }
	//
	// std::cout << std::endl << "wins :" << wins << " losses: " << losses << " ties: " << ties << std::endl;
	//
	// std::cout << std::endl;
	if(first)
		for (Node* node : children){
			node->printRoot(false);
		}

	if(first){
		std::cout << "}" << std::endl;
		std::cout << "end of print tree:" << std::endl;
	}

}


void Checkers::DoMCTSMove(){
    Checkers firstCopy;
    Checkers* firstCopy = new Checkers();
    this->firstCopy;
    firstCopy = *this;
    copyBoard = &firstCopy;
    root = new Node();
    currentState = root;

    int move = 0;
    double ratio = INT_MIN; //necessary?
	int simResult = INT_MIN;
	int player = 0; //necessary?
	bool isLeafNode = false;
	int bestMove = -1;

    int gIterations = 10;

    for(int i = 0; i < gIterations; ++i){
		// std::cout << "BEGIN NUMBER OF GAMES: " << i << std::endl;
        firstCopy = *this;
		copyBoard = &firstCopy;
		//selection of node to expand or roll out (changes currentRoot and gamecopy accordingly)
		select();
		//expand if needed
		expand();
		//simulate
		simResult = simulate(ratio);
	// 	//update the tree
        if ((whoistomove && simResult == 2) || (!whoistomove && simResult == 0)){												//win for MCTS player
			currentState->backPropagate(1, 0, 0);
			std::cout << "simresult == player!!!!!" << std::endl;
		}
		else if((whoistomove && simResult == 0) || (!whoistomove && simResult == 2)){		//loss for MCTS player
			currentState->backPropagate(0, 1, 0);
			std::cout << "simresult != player???????" << std::endl;
		}
		else if(simResult == 1){													//tie
			currentState->backPropagate(0, 0, 1);
            std::cout << "drawwww" << std::endl;
		}
        else{
            std::cout << "something went wrong unlucky" << std::endl;
        }
		// root->printTree();

	}
	// if(gMCTSprint == true){
	// 	root->printTree();
	// 	std::cout << "einde beurt-----------------------------------------------" << std::endl;
	// 	root->printRoot();
	// 	root->printAllChild();
	// }


    // root->printTree();
    root->printRoot();
    root->printAllChild();

	if(!root->isConsistent()){
		std::cout << "root is not consistent" << std::endl;
	}
	// 	//goto: select node
	// }
	if(root->children[0] != NULL){
		bestMove = root->maxChild(true);
        std::cout << "bestmove" << bestMove << std::endl;
	}


    std::vector<std::vector<int>> possiblemoves = availablemoves();
    std::cout << "do possible move" << std::endl;
    DoPossibleMove(possiblemoves[bestMove]);
	// game->doMove(bestMove,0);
    //TODO: Add whoistomove;
    std::cout << "currentstate rooot" << std::endl;
	currentState = root;

std::cout << "go clean tree" << std::endl;
	cleanTree();

}
void Checkers::cleanTree(){
    root->cleanTree();
}

void Checkers::select(){
	currentState = root;
	int move = -1;
	while(!currentState->isLeafNode()){
		move = currentState->maxChild(true);
		currentState = currentState->children[move];
        std::vector<std::vector<int>> possiblemoves = availablemoves();
        copyBoard->DoPossibleMove(possiblemoves[move]);
		//copyBoard->doMove(move, true);
	}
}

std::vector<std::vector<int>> Checkers::availablemoves(){
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
            // std::cout << "first take is true" << std::endl;

            possiblemoves = PossibleMovesBlackTake();
        }
        else {
            possiblemoves = PossibleMovesBlack();

        }
    }
    return possiblemoves;
}

void Checkers::expand(){
    if(currentState->getVisits() == 0){
		//do nothing, we want rollouts for this state
		return;
	}
	else{
		//We want to add a child for each possible move, then make currentState the first node and do rollout
		if(currentState->children.size() != 0){
			std::cout << "Er gaat iets fout in expand, we expanden terwijl er al kinderen zijn" << std::endl;
		}
		Node *node;
        std::vector<std::vector<int>> possiblemoves = copyBoard->availablemoves();
		for(size_t i = 0; i < possiblemoves.size(); ++i){ //TODO
			node = new Node(currentState);
			currentState->children.push_back(node);
		}

		if(currentState->children.size() > 0){//check if there is a child now (if not it's a end state)
			currentState = currentState->children[0];
			copyBoard->DoPossibleMove(possiblemoves[0]);
		}
	}
	return;
}

int Checkers::simulate(double &ratio){
	// std::cout << "we simuleren voor node:" << currentState->nodeNumber << std::endl;
    int nrmoves;
	return copyBoard->playthegame(50, 3, false, nrmoves, 0, 0);  //TODO: add random playout
}




int Checkers::playthegame(int maxgamelength, int depth, bool print,
                        int &nrmoves, int gametypeW, int gametypeB){
    
    
    

    int movecount = 0;
    
    while (movecount < maxgamelength){
        if (print)
            printboard();

        std::vector<std::vector<int>> possiblemoves;
        if (whoistomove){ //white to move
            if (FirstTakeWhite() || FirstTakeKing()){
                possiblemoves = PossibleMovesWhiteTake();
            }
            else {
                possiblemoves = PossibleMovesWhite();
            }
            //         for (size_t i = 0; i < possiblemoves.size(); i++){
            // std::cout << "possiblemoves: ";
            //     for (size_t j = 0; j < possiblemoves[i].size(); j++){
            //         std::cout << " " << possiblemoves[i][j];
         //        }
            // std::cout << std::endl;
       // }
            if (possiblemoves.empty())
                return 0; //black wins
            else{
                switch (gametypeW){
                    case 0: //random move
                        DoRandomMove();
                        break;
                    case 1:
                        DoMinimaxMove();
                        break;
                    case 2:
                        //DoMinimaxMoveAlphaBeta();
                        break;
                    case 3:
                        //DoMCTSmove();
                        break;
                }
            }
        }
        else { //black to move
            if (FirstTakeBlack() || FirstTakeKing()){
                possiblemoves = PossibleMovesBlackTake();
            }
            else {
                possiblemoves = PossibleMovesBlack();
            }

        // for (size_t i = 0; i < possiblemoves.size(); i++){
        //     std::cout << "possiblemoves: ";
        //         for (size_t j = 0; j < possiblemoves[i].size(); j++){
        //             std::cout << " " << possiblemoves[i][j];
        //         }
        //     std::cout << std::endl;
        // }
            if (possiblemoves.empty())
                return 2; //white wins
            else{
                switch (gametypeB){
                    case 0: //random move
                        DoRandomMove();
                        break;
                    case 1:
                        DoMinimaxMove();
                        break;
                    case 2:
                        //DoMinimaxMoveAlphaBeta();
                        break;
                    case 3:
                        DoMCTSMove();
                        break;
                }
            }
        }
        movecount++;
        promote();
        
    }
        nrmoves = movecount;
        return 1; //draw

}

int main(){

    Checkers Checkers;
    //Checkers.resetboard();
    //Checkers.playthegame();
    Checkers.whoistomove = false;
    int bestmove;
    int nrmoves;
    //Checkers.printboard();
    Checkers.resetboard();
    int result = Checkers.playthegame(200, 3, true, nrmoves, 0, 3);
    std::cout << "result: " << result << std::endl;

//  srand(100);
//     for (int i = 0; i < 10; i++)
//         Checkers.DoRandomMove();

    // Checkers.printboard();
} //main


//https://github.com/kurebasu/Dots-and-Boxes/blob/master/src/MCTSPlayer.cc