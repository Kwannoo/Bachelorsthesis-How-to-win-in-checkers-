#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>


int gNumberOfNodes;

class Node{
public:
	Node(Node* creator);							//constructor for children nodes
	Node();			//constructor for the root node
	~Node();													//destructor

	void cleanTree();

	bool isLeafNode();
	void backPropagate(int wins1, int losses1, int ties1);//function to propagate upwards in tree
	// void expand(int amountOfMoves, int noOfChildren);			//function to expand downwards in tree

	int getWins()	{return wins;}
	int getLosses()	{return losses;}
	int getTies()	{return ties;}
	int getVisits() {return wins+losses+ties;}

	int 		maxChild(bool justSelection = true);

	void 		printAllChild();
	double 	calcUCB1Value();
	bool 		isConsistent();
	void 		printTree(bool first = true);
	void 		printRoot(bool first = true);




	// static const int maxSize = 8;																//maximum dimentions of the board (in boxes)
	// static const int maxNoOfMoves = (2 * (maxSize+1) * maxSize);	//maximum number of doable moves in the beginning of the maxSize board is 2 * 9 * 8
	int rows, columns, maxNoOfMoves;																//all this information might be redundant
	int wins, losses, ties;
	bool isRoot;
	int nodeNumber;

	Node* parent;
	std::vector<Node*> children;

private:
	void updateValue();		//update the value of this tree according to children
};



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
        int evaluate();
        void DoMinimaxMove();
        bool HasToTake(int &i, int &j, int &i2, int &j2);

        int MinimaxAlgorithm(int depth, int &bestmove);
        void DoRandomMove();
        void DoMCTSMove();
        void select();
        void expand();
        int simulate(double &ratio);
        void cleanTree();
        std::vector<std::vector<int>> availablemoves();
        int playthegame(int maxgamelength, int depth, bool print,
                        int &nrmoves, int gametypeW, int gametypeB);

        
    private:
        Node* root;
        Node* currentState;
        int gNumberOfNodes;
        Checkers* copyBoard;

};


