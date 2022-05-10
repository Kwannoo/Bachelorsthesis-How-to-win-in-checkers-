#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>


class Checkers{
    public:

        bool whoistomove = false;
        char board[8][8] = {{'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'B', 'o', 'o', 'o', 'o'}, {'o', 'o', 'W', 'o', 'w', 'o', 'W', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
          {'w', 'o', 'w', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}, {'o', 'o', 'w', 'o', 'w', 'o', 'w', 'o'},
          {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} };
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
        std::vector<std::vector<int>> PossibleMovesWhiteTake();
        void PossibleMovesWhiteTakeMore(int i, int j, std::vector<std::vector<int>> &possiblemoves, std::vector<int> move);
        std::vector<std::vector<int>> PossibleMovesBlack();
        std::vector<std::vector<int>> PossibleMovesBlackTake();
        void PossibleMovesBlackTakeMore(int i, int j, std::vector<std::vector<int>> &possiblemoves, std::vector<int> move);

        bool FirstTakeWhite();
        bool FirstTakeBlack();
        bool FirstTakeKing();
        void DoPossibleMove(std::vector<int> possiblemoves);
        bool HasToTake(int &i, int &j, int &i2, int &j2);

        int* CopyBoard();
        int MinimaxAlgorithm(int depth, int &bestmove);


    private:

};