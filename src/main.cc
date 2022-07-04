#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>

#include "Checkers.cc"
#include "humanPlayerBlack.cc"
#include "humanPlayerWhite.cc"
#include "MCTSPlayer.cc"
#include "minimaxPlayer.cc"
#include "randomPlayer.cc"

void wrongInput(){
    std::cout << "please enter the right input" << std::endl;
}

int main (int argc, char* argv[]){

    if (argc != 8){
        wrongInput();
		return 1;
	}

    int numberOfGames = atoi(argv[1]);
    int giterations = atoi(argv[2]);
    int depth = atoi(argv[3]);
    bool print = atoi(argv[4]);
    int playerMode1 = atoi(argv[5]);
    int playerMode2 = atoi(argv[6]);
    int seed = atoi(argv[7]);
    
    
    srand(seed);
    Player* player1;
    Player* player2;

    Checkers* game = new Checkers();
    switch(playerMode1){
    case 0: player1 = new randomPlayer(game);
            std::cout << "player1 = randomPlayer" << std::endl;
            break;
    case 1: player1 = new minimaxPlayer(game);
            std::cout << "player1 = greedyPlayer" << std::endl;
            break;
    case 2: player1 = new humanPlayerBlack(game);
            std::cout << "player1 = MCPlayer" << std::endl;
            break;
    case 3: player1 = new MCTSPlayer(game);
            std::cout << "player1 = MCTSPlayer" << std::endl;
            break;
    default:std::cout << "speler " << playerMode1 << " bestaat niet, we kiezen de random speler voor 1" << std::endl;
            player1 = new randomPlayer(game);

    }

    switch(playerMode2){
    case 0: player2 = new randomPlayer(game);
            std::cout << "player2 = randomPlayer" << std::endl;
            break;
    case 1: player2 = new minimaxPlayer(game);
            std::cout << "player2 = greedyPlayer" << std::endl;
            break;
    case 2: player2 = new humanPlayerWhite(game);
            std::cout << "player2 = MCPlayer" << std::endl;
            break;
    case 3: player2 = new MCTSPlayer(game);
            std::cout << "player2 = MCTSPlayer" << std::endl;
            break;
    default:std::cout << "speler " << playerMode2 << " bestaat niet, we kiezen de random speler voor 1" << std::endl;
            player2 = new randomPlayer(game);

    }

    int player1Wins = 0;
    int player2Wins = 0;
    int ties = 0;
    double unused;
    int maximummoves = 100;
    int moves = 0;
    std::vector<std::vector<int>> possiblemoves;
	
    for (int i = 0; i < numberOfGames; i++){
		game->resetboard();
		game->TestBoard();
        do{
			std::cout << "------------------------------" << std::endl;
			
            if (!game->whoistomove){
				std::cout << "black to move" << std::endl;
                player1->doMove();
            }
            else{
				std::cout << "white to move" << std::endl;
                player2->doMove();
            }            
			moves++;
            possiblemoves = game->availableMoves();
			std::cout << "maximummoves: " << maximummoves << std::endl;
			game->printboard();
        } while (!possiblemoves.empty() && (moves < maximummoves));


			std::cout << "go out while loop \n";
			moves = 0;

			game->printboard();

			
            if (game->whoistomove && possiblemoves.empty())
                std::cout << "black wins" << std::endl;
                // return 0; //black wins
            
            else if (!game->whoistomove && possiblemoves.empty())
                std::cout << "white wins" << std::endl;
                // return 2; //white wins
            
            else 
                std::cout << "draw" << std::endl;
                //return 0;
			
    }
    delete player1;
    delete player2;
	delete game;
    return 0;
}

    