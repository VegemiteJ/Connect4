#ifndef NODE_H
#define NODE_H

#include "GameState.h"

class Node
{
public:
	//Public Constructors
	//-----------------------------

	//1. Called when constructing the root Node. 
	//    Must supply the initial state of the game board
	Node(int ID, GameState* initial, int initial_turn);

	//2. Called for children/ search tree initiailisation 
	//    Requires valid entry column for new move and turn of this node
	Node(int ID, GameState* parent_state, int new_mov_column, int new_turn);

	//Public Destructors
	//-----------------------------
	//Deallocates the utlity array and children utility based off
	//   Does not delete game state, as this is shared among search tree
	~Node();	

	void DeleteTree();

	//Public Member Functions
	//-----------------------------
	// Return a copy of gamestate containing the current move
	GameState* GetState();
	int GetTurn();
	int GetDepth();
	int GetNumberOfChildren();
	int GetUtil();
	int* GetChildrenUtil();
	Node** GetChildren();
	int GetMove();

	//Uses the current known board state to investigate possible moves
	Node** DiscoverChildren();

	//Returns the maximum utlity at this node position in order of 
	//    winUtil, h1Util, ....
	int ComputeUtil();

	//Print all detals of the node
	void Print();

	//Performs the move as designated by the initialiser
	void Move();
	//Remove the mve initialiy applied during constructor
	void UnMove();

private:
	//Private Member functions
	//-----------------------------
	int WinUtil();
	int H1Util();
	
	int ConnectivityUtil();

	//Helper Functions
	//-----------------------------
	int Count3(char Token);
	int DetermineDirection(int k, int l);	

	//Unused empty constructor
	Node();

	//Private Member vars
	//-----------------------------
	int ID;
	int thisMoveColumn;
	int thisMoveRow;
	int numChildren;
	int thisTurn;
	int allocated;
	int myUtil;
	int childUtil[7];
	Node** myChildren;
	Node* parent;
	GameState* state;
	
};

#endif