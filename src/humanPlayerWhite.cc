#include <iostream>

class humanPlayerWhite : public Player{
    public:
        humanPlayerWhite(Checkers* Checkers);	//constructor;
        void doMove();
    private:
};

humanPlayerWhite::humanPlayerWhite(Checkers* Checkers){
    game = Checkers;
}

void humanPlayerWhite::doMove(){
    bool valid = false;
    bool takemove = false;
    int i,j;
    int i2, j2;
    std::cout << "White to move: " << std::endl;
    do{
        game->printboard();
        if (game->FirstTakeWhite() || game->FirstTakeKing()){
            do{
                if (game->HasToTake(i, j, i2, j2))
                    takemove = true;
                else{
                    std::cout << "You have to take a piece!" << std::endl;
                    game->printboard();
                }
            } while(!takemove);
            if (game->validmovewhite(i, j, i2, j2)){ //if statement not needed but test
                valid = true;
            }
        }
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
            if (game->validmovewhite(i, j, i2, j2)){
                valid = true;
            }
            
            else
                std::cout << "Invalid move please enter correctly\n" << std::endl;
        }
            

    } while(!valid);
    
}

