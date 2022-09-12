int depth = 3;
int gIterations = 1000;
int moves = 0;
int maximummoves = 100;
int calls = 0;
int calls2 = 0;

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
#include "minimaxabPlayer.cc"

void wrongInput(){
    std::cout << "please enter the right input" << std::endl;
    std::cout << "./Checkers <numberOfGames> <gIterations> <depth> <print[0/1]> <playerMode1[0-3]> <playerMode2[0-3]> <seed>" << std::endl;
    std::cout << "Player modes: 0)randomPlayer   1)minimaxPlayer   2)humanPlayer   3)MCTSPlayer" << std::endl;
}

int main (int argc, char* argv[]){

    if (argc != 8){
        wrongInput();
		return 1;
	}

    int numberOfGames = atoi(argv[1]);
    gIterations = atoi(argv[2]);
    depth = atoi(argv[3]);
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
            std::cout << "player1 =  minimaxPlayer" << std::endl;
            break;
    case 2: player1 = new humanPlayerBlack(game);
            std::cout << "player1 = humanPlayer" << std::endl;
            break;
    case 3: player1 = new MCTSPlayer(game);
            std::cout << "player1 = MCTSPlayer" << std::endl;
            break;
    case 4: player1 = new minimaxabPlayer(game);
            std::cout << "player2 = minimaxAlphaBeta" << std::endl;
            break;
    default:std::cout << "speler " << playerMode1 << " bestaat niet, we kiezen de random speler voor 1" << std::endl;
            player1 = new randomPlayer(game);

    }

    switch(playerMode2){
    case 0: player2 = new randomPlayer(game);
            std::cout << "player2 = randomPlayer" << std::endl;
            break;
    case 1: player2 = new minimaxPlayer(game);
            std::cout << "player2 = minimaxPlayer" << std::endl;
            break;
    case 2: player2 = new humanPlayerWhite(game);
            std::cout << "player2 = humanPlayer" << std::endl;
            break;
    case 3: player2 = new MCTSPlayer(game);
            std::cout << "player2 = MCTSPlayer" << std::endl;
            break;
    case 4: player2 = new minimaxabPlayer(game);
            std::cout << "player2 = minimaxAlphaBeta" << std::endl;
            break;
    default:std::cout << "speler " << playerMode2 << " bestaat niet, we kiezen de random speler voor 1" << std::endl;
            player2 = new randomPlayer(game);

    }

    int player1Wins = 0;
    int player2Wins = 0;
    int draws = 0;
    double unused;
    int totalmoves = 0;
    std::vector<std::vector<int>> possiblemoves;
	
    for (int i = 0; i < numberOfGames; i++){
		game->resetboard();
		game->doRandomMove();
        game->doRandomMove();
        
        do{	

        if (!game->whoistomove){
            player1->doMove();
        }
        else{
            player2->doMove();
        }     
			moves++;
            possiblemoves = game->availableMoves();
			
        } while (!possiblemoves.empty() && (moves < maximummoves));
 

            totalmoves += moves;
			
            game->printboard();
			
            if (game->whoistomove && possiblemoves.empty()){
                std::cout << "black wins" << std::endl;
                player1Wins++;
                // return 0; //black wins
            }
            else if (!game->whoistomove && possiblemoves.empty()){
                std::cout << "white wins" << std::endl;
                player2Wins++;
            }
                // return 2; //white wins
            else {
                std::cout << "draw" << std::endl;
                draws++;
            }

            std::cout << moves << " :--------------------------------------" << std::endl;
			moves = 0;
    }

    std::cout << "player1 black wins: " << player1Wins << std::endl;
    std::cout << "player2 white wins: " << player2Wins << std::endl;
    std::cout << "draws: " << draws << std::endl;
    std::cout << "average amount of moves: " << totalmoves/numberOfGames << std::endl;
    std::cout << "average amount of minimax calls per game: " << calls/numberOfGames << std::endl;
    std::cout << "average amount of minimaxab calls per game: " << calls2/numberOfGames << std::endl;

    delete player1;
    // delete player2;
	delete game;

    return 0;
}

    