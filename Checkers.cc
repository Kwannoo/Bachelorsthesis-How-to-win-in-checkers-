#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
#include "Checkers.h"


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
                    blackpieces++;
                }
                else{
                    board[i][j] = 'o';
                }
            }
            else if (i > 4){
                if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)){
                    board[i][j] = 'w';
                    whitepieces++;
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
}

//*************************************************************************

bool Checkers::checkpiece(int i, int j){

    if (i < 0 || i > 8 || j < 0 || j > 8)
        return false; 

    if (board[i][j] != 'o')
        return true;


    return false;
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
                    blackpieces--;
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
                    blackpieces--;
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

void Checkers::playthegame(){
    while (blackpieces != 0 || whitepieces != 0){
        if (!whoistomove){
            dohumanblackmove();
        }
        else{
            dohumanwhitemove();
        }
        whoistomove = !whoistomove;
        promote();
        //printboard();
    }

    std::cout << "game is done" << std::endl;
}


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
                    whitepieces--;
                    TakeExtraBlack(i+2, j-2);
                    return true;
                }
                    
            }
            if (j + 1 == j2){
                if (board[i+2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i+1][j+1] = 'o'; //take black piece
                    board[i+2][j+2] = 'b';
                    whitepieces--;
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
                    if (!whoistomove)
                        whitepieces--;
                    else
                        blackpieces--;
                    TakeExtraKing(i+2, j-2);
                    return true;
                }
                    
            }
            if (i - 1 == i2 && j - 1 == j2){
                if (board[i-2][j-2] == 'o'){
                    board[i][j] = 'o';
                    board[i-1][j-1] = 'o'; 
                    board[i-2][j-2] = Player;
                    if (!whoistomove)
                        whitepieces--;
                    else
                        blackpieces--;
                    TakeExtraKing(i-2, j-2);
                    return true;
                }
            }
            if (i - 1 == i2 && j + 1 == j2){
                if (board[i-2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i-1][j+1] = 'o'; //take piece
                    board[i-2][j+2] = Player;
                    if (!whoistomove)
                        whitepieces--;
                    else
                        blackpieces--;
                    TakeExtraKing(i-2, j+2);
                    return true;
                }
                    
            }
            if (i + 1 == i2 && j + 1 == j2){
                if (board[i-2][j+2] == 'o'){
                    board[i][j] = 'o';
                    board[i+1][j+1] = 'o'; //take piece
                    board[i+2][j+2] = Player;
                    if (!whoistomove)
                        whitepieces--;
                    else
                        blackpieces--;
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
        printboard();
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
                    blackpieces--;
                    i -= 2;
                    j -= 2;
                }
                else if (i2 == i-1 && j2 == j+1 && (board[i2][j2] == 'b' || board[i2][j2] == 'B')){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i-2][j+2] = 'w';
                    blackpieces--;
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
        printboard();
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
                    whitepieces--;
                    i += 2;
                    j -= 2;
                }
                else if (i2 == i+1 && j2 == j+1 && (board[i2][j2] == 'w' || board[i2][j2] == 'W')){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j+2] = 'b';
                    whitepieces--;
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
        printboard();
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
                    if (!whoistomove)
                        whitepieces--; //piece taken
                    else 
                        blackpieces--;
                    i -= 2;
                    j -= 2;
                }
                else if (i2 == i-1 && j2 == j+1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i-2][j+2] = Player;
                    if (!whoistomove)
                        whitepieces--; //piece taken
                    else 
                        blackpieces--;
                    i -= 2;
                    j += 2;
                }
                else if (i2 == i+1 && j2 == j-1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j-2] = Player;
                    if (!whoistomove)
                        whitepieces--; //piece taken
                    else 
                        blackpieces--;
                    i += 2;
                    j -= 2;
                }
                else if (i2 == i+1 && j2 == j+1 && (board[i2][j2] == Opponent || board[i2][j2] == Opponent+32)){
                    board[i][j] = 'o';
                    board[i2][j2] = 'o';
                    board[i+2][j+2] = Player;
                    if (!whoistomove)
                        whitepieces--; //piece taken
                    else 
                        blackpieces--;
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
                    if (j-2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden white" << std::endl;
                        return true;
                    }
                }
                else if ((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o' ){
                    if (j+2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden white" << std::endl;
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
                    if (j-2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
                }
                else if ((board[i-1][j+1] == Opponent || board[i-1][j+1] == Opponent+32) && board[i-2][j+2] == 'o' ){
                    if (j+2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
                }
                else if ((board[i+1][j-1] == Opponent || board[i+1][j-1] == Opponent+32) && board[i+2][j-2] == 'o' ){
                    if (j-2 > 0 && i+2 > 0){
                        std::cout << "first take gevonden king" << std::endl;
                        return true;
                    }
                }
                else if ((board[i+1][j+1] == Opponent || board[i+1][j+1] == Opponent+32) && board[i+2][j+2] == 'o' ){
                    if (j+2 > 0 && i+2 > 0){
                        std::cout << "first take gevonden king" << std::endl;
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
                    if (j+2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden black" << std::endl;
                        return true;
                    }
                }
                else if ((board[i+1][j+1] == 'w' || board[i+1][j+1] == 'W') && board[i+2][j+2] == 'o' ){
                    if (j+2 > 0 && i+2 > 0){
                        std::cout << "first take gevonden black" << std::endl;
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
        //  {'o', 'o', 'o', 'o', 'o', 'b', 'o', 'o'}, {'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o'}};

}

std::vector<std::vector<int>> Checkers::PossibleMovesWhite(){
    std::vector<std::vector<int>> possiblemoves;
    std::vector<int> move;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == 'w' || board[i][j] == 'W'){
                if (board[i-1][j-1] == 'o'){
                    move = {i,j,i-1,j-1};
                    possiblemoves.push_back(move);
                }
                if (board[i-1][j+1] == 'o'){
                    move = {i,j,i-1,j-1};
                    possiblemoves.push_back(move);
                }
                if (board[i][j] == 'W'){
                    if (board[i+1][j-1] == 'o'){
                        move = {i,j,i+1,j-1};
                        possiblemoves.push_back(move);
                    }
                    if (board[i+1][j+1] == 'o'){
                        move = {i,j,i+1,j+1};
                        possiblemoves.push_back(move);
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

    //if white wins return 1000

    //if black wins return 1000

    //if depth has been reached evaluate()

    if (whoistomove){
        int maxValue = -1000000;
        memcpy (copyboard, board, 8*8*sizeof(int));
        //if can take
        //possiblemovestake
        //else
        possiblemoves = PossibleMovesWhite();


        for (size_t i = 0; i < possiblemoves.size(); i++){
            //dowhitemove(i);
            //int eval = minimaxalgorithm(depth-1, dummymove)
			// if (eval > maxValue){
			// 	bestmove = i;
			// 	maxValue = eval;
			// }
            //memcpy(board, copyboard, 8*8*sizeof(int));
        }
        return maxValue;
    
    }

    else{
        return 0;
    }
    return 0;
}

// int* Checkers::CopyBoard(){
//     static int copyboard[8][8];
//     for (int i = 0; i < 8; i++){
//         for (int j = 0; j < 8; j++)
//             copyboard[i][j] = board[i][j];
//     }
//     return copyboard;
// }

std::vector<std::vector<int>> Checkers::PossibleMovesWhiteTake(){
    std::vector<std::vector<int>> possiblemoves;
    std::vector<int> move;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 'w'){
                if ((board[i-1][j-1] == 'b' || board[i-1][j-1] == 'B') && board[i-2][j-2] == 'o' ){
                    if (j-2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden possiblemoves white" << std::endl;
                        return true;
                    }
                }
                else if ((board[i-1][j+1] == 'b' || board[i-1][j+1] == 'B') && board[i-2][j+2] == 'o' ){
                    if (j+2 > 0 && i-2 > 0){
                        std::cout << "first take gevonden white" << std::endl;
                        return true;
                    }
                }
    }
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

int main(){

    Checkers Checkers;
    Checkers.resetboard();
    Checkers.playthegame();
} //main