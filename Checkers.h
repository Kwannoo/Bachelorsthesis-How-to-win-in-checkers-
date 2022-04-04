#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>


class Checkers{
    public:

        bool whoistomove = true;
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
        void playthegame();
        void promote();
        bool validmoveblacknormal(int i, int j, int i2, int j2);
        bool validmovewhitenormal(int i, int j, int i2, int j2);
        bool validmoveking(int i, int j, int i2, int j2);
        void TakeExtraWhite(int i, int j);
        void TakeExtraBlack(int i, int j);
        void TakeExtraKing(int i, int j);
        void TestBoard();
        std::vector<std::vector<int>> PossibleMovesWhite();
        bool FirstTakeWhite(int &takei, int &takej, int &takei2, int &takej2);
        bool FirstTakeBlack(int &takei, int &takej, int &takei2, int &takej2);
        bool FirstTakeKing(int &takei, int &takej, int &takei2, int &takej2);
        bool HasToTake();
        int MinimaxAlgorithm(int depth, int &bestmove);


    private:

};