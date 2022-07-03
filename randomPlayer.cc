
class randomPlayer : public Player{
    public:
        randomPlayer(Checkers* Checkers);	//constructor;
        ~randomPlayer();	//constructor;
        void doRandomMove();
    private:

};

randomPlayer::randomPlayer(Checkers* Checkers){
    game = Checkers;
}

randomPlayer::~randomPlayer(){

}

void randomPlayer::doRandomMove(){
    game->doRandomMove();
}