#include "AlphaBetaAI.h"
#include "DebugLogger.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>

AlphaBetaAI::AlphaBetaAI() {}

AlphaBetaAI::AlphaBetaAI(Move _p)
{
    player = _p;
    MaxDepth = 6;
    GlobalPrunes = 0;
    NodesExplored = 0;
    MakingFirstMoveOfGame = false;

    generator.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());
    distribution = uniform_int_distribution<int>(1, 1000);
    dice = bind(distribution, generator);
}

void AlphaBetaAI::Reset()
{
    GlobalPrunes = 0;
    NodesExplored = 0;
    BestMove = 0;
    BestUtility = 0;
    CurrentBoard = nullptr;
}

int AlphaBetaAI::DepthNormalise(int value)
{
    if (value<0) {
        value++;
    }
    else if (value>0) {
        value--;
    }
    return value;
}

int AlphaBetaAI::AlphaBeta(int _depth, int _alpha, int _beta, bool _maxPlayer)
{
	//Check If P1 has won, return positive utlity
	//Check if P2 has won, return negative utility
	//IF I am P1 -> call with maxplayer
	//Check if terminal depth reached, i.e. depth == 0

	//Recursive Case
	//Randomise child search order
	//If max player do->
	//Else ->
	//For each child
	//	Make move
	//	Evaluate AB on that board
	//	Unmake move
	//	Check cost conditions
	//	Check alpha beta

	//Debug Print statements - TODO: Move to debug printer
	int indentlvl = MaxDepth - _depth;
	NodesExplored++;

	printString(std::cout, 2, indentlvl,"Called AB with d:" + to_string(_depth) + " alpha: " + to_string(_alpha) + " beta: " + to_string(_beta) + "\n");
	printString(std::cout, 2, indentlvl,"Maximising: " + to_string(_maxPlayer)+"\n");
	printString(std::cout, 3, CurrentBoard->ToString((MaxDepth - _depth)) + "\n");
	if (gse.CheckWin(CurrentBoard, P1_MOVE)) {
		return gse.ComputeWinUtility(CurrentBoard, P1_MOVE);
	}
	else if (gse.CheckWin(CurrentBoard, P2_MOVE)) {
		return gse.ComputeWinUtility(CurrentBoard, P2_MOVE);
	}

	//Base case at expired depth OR when no more valid moves
	vector<int> allValidMoves = CurrentBoard->GetAllValidMoves();
	if (allValidMoves.size() == 0) {
		int util = gse.ComputeUtility(CurrentBoard);
		printString(std::cout, 3, indentlvl,"Reached terminal move count - no more valid moves...\n");
		printString(std::cout, 3, indentlvl,"util: " + to_string(util) + "\n");
		return util;
	}
	if (_depth == 0) {
		int util = gse.ComputeUtility(CurrentBoard);
		printString(std::cout, 3, indentlvl,"util: " + to_string(util) + "\n");
		return util;
	}
	//Recursion case
	//===============================
	int costValue;
	int bestValue;
	size_t numRandSwaps = allValidMoves.size();
	for (size_t i = 0; i<numRandSwaps; i++) {
		//Swap two random elements
		int a = dice() % numRandSwaps;
		int b = dice() % numRandSwaps;
		SwapTwoElements(allValidMoves[a], allValidMoves[b]);
	}

	if (_maxPlayer) {
		bestValue = -INF;
		for (auto i : allValidMoves) {
			CurrentBoard->MakeMove(i+1, P1_MOVE);
			printString(std::cout, 3, indentlvl, "Making Move: " + to_string(i + 1) + "...\n");
			costValue = AlphaBeta(_depth - 1, _alpha, _beta, !_maxPlayer);
			costValue = DepthNormalise(costValue);
			CurrentBoard->UnMakeMove(i + 1);
			printString(std::cout, 3, indentlvl, "Cost: " + to_string(costValue) + "\n");
			if (costValue > bestValue) {
				printString(std::cout, 3, indentlvl, "Higher value: " + to_string(costValue) + "\n");
				bestValue = costValue;
				if (_depth == (MaxDepth)) {
					BestMove = i;
					printString(std::cout, 3, indentlvl, "Best Move: " + to_string(BestMove+1) + "\n");
				}
			}
			_alpha = (_alpha >= bestValue) ? _alpha : bestValue;
			if (_beta <= _alpha) {
				break;
			}
		}
	}
	else {
		bestValue = INF;
		for (auto i : allValidMoves) {
			CurrentBoard->MakeMove(i + 1, P2_MOVE);
			printString(std::cout, 3, indentlvl, "Making Move: " + to_string(i + 1) + "...\n");
			costValue = AlphaBeta(_depth - 1, _alpha, _beta, !_maxPlayer);
			costValue = DepthNormalise(costValue);
			CurrentBoard->UnMakeMove(i+1);
			printString(std::cout, 3, indentlvl, "Cost: " + to_string(costValue) + "\n");
			if (costValue < bestValue) {
				printString(std::cout, 3, indentlvl, "Lower value: " + to_string(costValue) + "\n");
				bestValue = costValue;
				if (_depth == (MaxDepth)) {
					BestMove = i;
					printString(std::cout, 3, indentlvl, "Best Move: " + to_string(BestMove+1) + "\n");
				}
			}
			_beta = (_beta <= bestValue) ? _beta : bestValue;
			if (_beta <= _alpha) {
				break;
			}
		}
	}
	return bestValue;
}

void AlphaBetaAI::SwapTwoElements(int &a, int &b)
{
    int temp = a;
	a = b;
	b = temp;
}
///Return the 1-indexed best move found
int AlphaBetaAI::GetBestMove()
{
    return BestMove+1;
}

void AlphaBetaAI::Play(Board * _CurrentBoard)
{
	printString(std::cout, 1, "================================\n");
	printString(std::cout, 1, "Making a play\n");
    
	//Copy of board for modifications
    CurrentBoard = _CurrentBoard;
	NodesExplored = 0;
	BestMove = INT_MAX;	//Reset to 0xefffffffffffff

    //Setup run
	BestUtility = AlphaBeta(MaxDepth, INT_MIN, INT_MAX, (player == P1_MOVE));

    printString(std::cout,1, "Player 1: " + to_string(player == P1_MOVE) + "\n");
    printString(std::cout,1, "Utility: " + to_string(BestUtility) + "\n");
    printString(std::cout,1, "Explored: " + to_string(NodesExplored) + "\n");
    printString(std::cout,1, "Pruned: " + to_string(GlobalPrunes) + "\n");
	printString(std::cout,1, "================================\n");
}