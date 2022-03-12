#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>

class Checkers{
    public:

        bool whoistomove = false;
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

    private:

};