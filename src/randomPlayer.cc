
class randomPlayer : public Player{
    public:
        randomPlayer(Checkers* Checkers);	//constructor;
        ~randomPlayer();	//constructor;
        void doMove();
    private:

};

randomPlayer::randomPlayer(Checkers* Checkers){
    game = Checkers;
}

randomPlayer::~randomPlayer(){

}

void randomPlayer::doMove(){
    game->doRandomMove();
}