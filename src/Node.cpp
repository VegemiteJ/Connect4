#include "Node.h"
#include "Consts.h"
#include "ColourDef.h"
#include <iostream>

int global_id = 0;

using namespace std;

//Public Constructors
//---------------------------------------------------
Node::Node() {}	//Unused

Node::Node(int iID, GameState* iinitial, int initial_turn) :
	ID(iID), thisMoveColumn(-1), numChildren(-1), thisTurn(initial_turn), 
	allocated(0), myUtil(0), myChildren(NULL), 
	parent(NULL), state(iinitial)
	{
		childUtil = new int[state->numCols];
		allocated = 1;
	}

Node::Node(int iID, GameState* parent_state, int new_mov_column, int new_turn) :
	ID(iID), thisMoveColumn(new_mov_column), numChildren(-1), thisTurn(new_turn), 
	allocated(0), myUtil(0), myChildren(NULL), 
	parent(NULL), state(parent_state) 
	{
		childUtil = new int[state->numCols];
		allocated = 1;
	}

//Public Destructors
//---------------------------------------------------
Node::~Node() 
{
	if (verbose>3)
		cout << "Deleting node: " << ID << endl;
	if (allocated==1)
		delete[] childUtil;		//Why does New[] throwing segfault after 15 deep or so on linux
								//Mem usage is only 800MB for 15 deep... so that isn't the issue
}
void Node::DeleteTree() {}

//Public Member Functions
//---------------------------------------------------
GameState* Node::GetState()
{
	//Return a copy of the game state
	return state;
}
int Node::GetTurn() 
{
	return thisTurn;
}
int Node::GetDepth() 
{
	return 0;
}
int Node::GetNumberOfChildren() 
{
	return numChildren;
}
int Node::GetUtil() 
{
	return myUtil;
}
int* Node::GetChildrenUtil() 
{
	return childUtil;
}
Node** Node::GetChildren() 
{
	return myChildren;
}
int Node::GetMove() 
{
	return thisMoveColumn;
}

Node** Node::DiscoverChildren() 
{
	if (verbose>3) {
		cout << "Discover Children..." << endl;
		cout << "Num Rows: " << state->numRows << "Num Cols: " << state->numCols << endl;
	}
	numChildren = 0;

	int terminalPosition = 0;
	int children[state->numCols];

	//Discover number of children
	for (int i=0; i<state->numCols; i++) {
		if (state->checkValidMove(i)){
			children[numChildren++] = i;
			terminalPosition++;
			if (verbose >3)
				cout << "Column: " << i << " " << children[numChildren-1];
		}
	}
	if (verbose >3)
		cout << "NumChild: " << numChildren << endl;
	if (numChildren != 0) {
		myChildren = new Node*[numChildren];
		allocated = 1;
	}
	//childUtil = new int[numChildren]();		Why is New[] throwing segfault????
	for (int i = 0; i<terminalPosition; i++){
		if (verbose>3)
			cout << "Making node: " << i << endl;
		myChildren[i] = new Node(global_id++, state, children[i], (thisTurn+1)%2);
	}
	//Free local scope children array
	//delete[] children;	Why is New[] throwing segfault????

	return myChildren;
}

int Node::ComputeUtil() 
{
	int winStat = WinUtil();
	if (winStat != 0) {
		myUtil = winStat;
		return winStat;
	}
	int h1Stat = H1Util();
	if (h1Stat != 0) {
		myUtil = h1Stat;
		return h1Stat;
	}
	//Purely neutral statistic
	myUtil = 0;
	return 0;
}
void Node::Print() 
{
	cout << "\nID: " << ANSI_PURPLE << ID << ANSI_RESET;
	cout << " Number of Children: " << ANSI_PURPLE;
	cout << numChildren << ANSI_RESET;
	cout << " Turn: " << ANSI_PURPLE << thisTurn << ANSI_RESET;
	cout << endl;
	state->print();
	cout << "Last Move: " << state->LastMoveRow + 1 << " " << state->LastMoveCol + 1 << endl;
	cout << "X Win?: " << state->checkWin('X') << ", O Win?: " << state->checkWin('O') << endl;
	cout << "This State Utility: " << ANSI_PURPLE << ComputeUtil() << ANSI_RESET << "\n" << endl;
}

//Private Member Functions
//---------------------------------------------------
void Node::Move() 
{
	char turn = (thisTurn == 0) ? 'X' : 'O';
	state->update_cell(thisMoveColumn, turn);
	thisMoveRow = state->LastMoveRow;
}
void Node::UnMove() 
{
	if (verbose>3)
		cout << "Unmoving... Row: " << thisMoveRow+1 << " Col: " << thisMoveColumn+1 << endl;

	char** st = state->getState();
	st[thisMoveRow][thisMoveColumn] = ' ';
}
int Node::WinUtil() 
{
	char thisTurnToken = (thisTurn==0) ? 'X' : 'O';
	char currentCheckToken1 = 'X';
	char currentCheckToken2 = 'O';
	if (verbose>3) {
		cout << "thisTurnToken = " << thisTurnToken << endl;
		cout << "Stat1: " << state->checkWin(currentCheckToken1) << " " << (currentCheckToken1==thisTurnToken) << endl;
		cout << "Stat2: " << state->checkWin(currentCheckToken2) << " " << (currentCheckToken2==thisTurnToken) << endl;
	}
	// If this turn has won, return max util
	if (state->checkWin(currentCheckToken1) && currentCheckToken1 == thisTurnToken)
	{
		if (verbose >3)
			cout << "Player X Appears to have won, returning max utility" << endl;
		int base = 1000;
		return base;
	}
	else if (state->checkWin(currentCheckToken2) && currentCheckToken2 == thisTurnToken)
	{
		if (verbose >3)
			cout << "Player O Appears to have won, returning min utility" << endl;
		int base = -1000;
		return base;
	}
	return 0;
}

int Node::H1Util() 
{
	//Number of X and O in a row
	int count[2] = {0,0};
	
	char currentToken = 'X';
	count[0] = Count3(currentToken);

	currentToken = 'O';
	count[1] = Count3(currentToken);

	if (verbose>3) {
		cout << "Number of 3 in a row for X: " << count[0] << endl;
		cout << "Number of 3 in a row for O: " << count[1] << endl;
	}

	return 50*(count[0]-count[1]);
}

int Node::DetermineDirection(int k, int l)
{
	int val = l+k;
	val = (val<0) ? -val : val;

	if (val==2)			//Left diag
		return 0;
	else if (val==0)	//Right diag
		return 1;
	else if (l==0)		//Vertical
		return 2;
	else if (k==0)		//Horizontal
		return 3;

	//Error
	return -1;
}

int Node::Count3(char Token)
{
	int nRows = state->numRows;
	int nCols = state->numCols;

	int count = 0;

	char** brd = state->getState();

	//For each square on board not already seen
	for (int i=0; i<nRows; i++) {
		for (int j=0; j<nCols; j++) {
			if ( (brd[i][j] == ' ')) {		//If current square is blank
				//Initialise array of 4 ints storing the number in a row in each dimension
				int countInDimension[4] = {0,0,0,0};	//1 for including self

				//Check from this position - all neighbouring pieces
				for (int k=-1; k<=1; k++) {		//While in bounds rows, columns
					if ((i+k < nRows && i+k >= 0)) {
						for (int l=-1; l<=1; l++) {
							if ((j+l >= 0) && (j+l < nCols) && (k!=0 || l!=0)) {
								//If current neighbour is unvisited, continue down that dimension incrementing length
								//Only continue if unvisited && token is same one && not out of bounds
								int row = i+k;
								int col = j+l;
								int index = DetermineDirection(k,l);
								while (brd[row][col] == Token) {
									//cout << "Position: (" << row << "," << col << ") is " << Token << endl;
									countInDimension[index]++;

									row += k; col += l;
									if (row<0 || row>=nRows || col<0 || col>=nCols) {	//Out of bounds
										break;
									}
								}
							}
						}
					}
				}
				//cout << "Dimension details: " << countInDimension[0] << " " << countInDimension[1] << " " << countInDimension[2] << " " << countInDimension[3] << endl;
				int max = 0;
				for (int m=0; m<4; m++) {
					if (countInDimension[m] > max) {
						max = countInDimension[m];
					}
				}
				if (max == 3) {
					//cout << "Found a 3 in Row for " << Token << " at: (" << i << "," << j << ")" << endl;
					count++;
				}
			}
		}
	}

	return count;
}

int Node::ConnectivityUtil() 
{
	return 0;
}
