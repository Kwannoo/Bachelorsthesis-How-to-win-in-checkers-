#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
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

//startpos i en j || endpos i en j
bool Checkers::validmovewhite(int i, int j, int i2, int j2){
    if (i < 0 && i > 8 && j < 0 && j > 8) //out of bounds
        return false;

    if ((j - 1 == j2 || j + 1 == j2) && i - 1 == i2){
        if (board[i2][j2] == 'o'){ //return true
            return true;
        }
        if (board[i2][j2] == 'b'){
            if (j - 1 == j2){
                if (board[i-2][j-2] == 'o'){
                    board[i-1][j-2] = 'o'; //take black piece
                    blackpieces--;
                    return true;
                }
                    
            }
            if (j + 1 == j2){
                if (board[i-2][j+2] == 'o'){
                    board[i-1][j-2] = 'o'; //take black piece
                    blackpieces--;
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
    // std::cout << "i: " << i << " j: " << j << std::endl;
    // std::cout << "i2: " << i2 << " j2: " << j2 << std::endl;


    if (i < 0 && i > 8 && j < 0 && j > 8){
        return false;
    } //out of bounds


    if ((j - 1 == j2 || j + 1 == j2) && i + 1 == i2){
        if (board[i2][j2] == 'o'){ //return true
            return true;
        }
        if (board[i2][j2] == 'w'){
            if (j - 1 == j2){
                if (board[i+2][j+2] == 'o'){
                    board[i+1][j-2] = 'o'; //take white piece
                    whitepieces--;
                    return true;
                }
                    
            }
            if (j + 1 == j2){
                if (board[i+2][j+2] == 'o'){
                    board[i+1][j-2] = 'o'; //take black piece
                    whitepieces--;
                    return true;
                }
            }
        }

    } 

    return false;

}

//*************************************************************************

void Checkers::dohumanwhitemove(){
    bool valid = false;
    int i,j;
    int i2, j2;
    std::cout << "White to move: " << std::endl;
    do{
        std::cout << "Which piece would you like to move?" << std::endl;
        std::cout << "Fill in horizontal coordinate (0-7)" << std::endl;
        std::cin >> j;
        std::cout << "Fill in vertical coordinate (0-7)" << std::endl;
        std::cin >> i;
        if (checkpiece(i, j)){
            std::cout << "Where do you want your piece to move?" << std::endl;
            std::cout << "Fill in horizontal coordinate (0-7)" << std::endl;
            std::cin >> j2;
            std::cout << "Fill in vertical coordinate (0-7)" << std::endl;
            std::cin >> i2;
            if (validmovewhite(i, j, i2, j2)){
                    board[i][j]  = 'o';
                    board[i2][j2] = 'w';
                    valid = true;
            }
            else{
                std::cout << "Invalid move please enter correctly\n" << std::endl;
            }
        }
        else{
            std::cout << "Invalid move please enter correctly\n" << std::endl;
        }


    } while(!valid);
    
    
}


//*************************************************************************

void Checkers::dohumanblackmove(){
    bool valid = false;
    int i,j;
    int i2, j2;

    std::cout << "Black to move: " << std::endl;
    do{
        std::cout << "Which piece would you like to move?" << std::endl;
        std::cout << "Fill in horizontal coordinate (0-7)" << std::endl;
        std::cin >> j;
        std::cout << "Fill in vertical coordinate (0-7)" << std::endl;
        std::cin >> i;
        if (checkpiece(i, j)){
            std::cout << "Where do you want your piece to move?" << std::endl;
            std::cout << "Fill in horizontal coordinate (0-7)" << std::endl;
            std::cin >> j2;
            std::cout << "Fill in vertical coordinate (0-7)" << std::endl;
            std::cin >> i2;
            if (validmoveblack(i, j, i2, j2)){
                    board[i][j]  = 'o';
                    board[i2][j2] = 'b';
                    valid = true;
            }
            else{
                std::cout << "Invalid move please enter correctly\n" << std::endl;
            }
        }
        else{
            std::cout << "Invalid move please enter correctly\n" << std::endl;
        }


    } while(!valid);
    
    
}

//*************************************************************************

int main(){
    Checkers Checkers;
    Checkers.resetboard();
    Checkers.printboard();
    Checkers.dohumanwhitemove();
    Checkers.printboard();
    Checkers.dohumanblackmove();
    Checkers.printboard();
} //main