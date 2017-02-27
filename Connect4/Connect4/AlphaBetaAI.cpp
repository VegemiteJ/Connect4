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

int AlphaBetaAI::AlphaBeta(int _move, int _depth, int _alpha, int _beta, bool _maxPlayer, Move p)
{
    printString(std::cout, 2, "\n\nCalled AB Search at depth: " + to_string(_depth) + "\n");
    NodesExplored++;

    MaxDepth = (_depth > MaxDepth ? _depth : MaxDepth);

    //Make the move on the board - if not the first move of the game
    if (!(_depth == MaxDepth && MakingFirstMoveOfGame))
    {
        (*CurrentBoard).MakeMove(_move + 1, p);
    }
    
    printString(std::cout, 2, "Making move: " + to_string(_move+1) + "\n");
    printString(std::cout, 3, "Board looks like\n" + CurrentBoard->ToString() + "\n");

    //Base Case: If depth is zero or either wins - return the utility
    if (gse.CheckWin(CurrentBoard, P1_MOVE))
    {
        printString(std::cout, 2, "Player win detected " + to_string(player) + " " + to_string(P1_MOVE) + "\n");
        if (!(_depth == MaxDepth && MakingFirstMoveOfGame))
        {
            (*CurrentBoard).UnMakeMove(_move + 1);
        }
        return gse.ComputeWinUtility(CurrentBoard, player, P1_MOVE);
    }
    if (gse.CheckWin(CurrentBoard, P2_MOVE))
    {
        printString(std::cout, 2, "Player win detected " + to_string(player) + " " + to_string(P2_MOVE) + "\n");
        if (!(_depth == MaxDepth && MakingFirstMoveOfGame))
        {
            (*CurrentBoard).UnMakeMove(_move + 1);
        }
        return gse.ComputeWinUtility(CurrentBoard, player, P2_MOVE);
    }
    if (_depth == 0)
    {
        printString(std::cout, 2, "Terminal depth reached\n");
        if (!(_depth == MaxDepth && MakingFirstMoveOfGame))
        {
            (*CurrentBoard).UnMakeMove(_move + 1);
        }
        return gse.ComputeUtility(CurrentBoard, _depth);
    }

    //Recursion case:
    //If we are the maximum player: 
    //For all valid child moves
    //      Call AB(child move)
    //      Extract the utility
    //  If value better than best value -> set as best value and best move
    //  If best value higher than alpha -> set alpha
    //  Break if beta <= alpha due to pruned branch
    int costValue;
    int bestValue;
    vector<int>* allValidMoves = CurrentBoard->GetAllValidMoves();
    size_t numRandSwaps = allValidMoves->size();
    for (size_t i = 0; i<numRandSwaps; i++) {
        //Swap two random elements
        int a = dice() % allValidMoves->size();
        int b = dice() % allValidMoves->size();
        SwapTwoElements(&(*allValidMoves)[a], &(*allValidMoves)[b]);
    }

    if (_maxPlayer)
    {
        printString(std::cout, 3, "Maximum player searching...\n");
        bestValue = -INF;
        for (int i = 0; i < allValidMoves->size(); i++)
        {
            costValue = AlphaBeta((*allValidMoves)[i], _depth - 1, _alpha, _beta, false, (p == P1_MOVE ? P2_MOVE : P1_MOVE));
            costValue = DepthNormalise(costValue);
            printString(std::cout, 3, "Child " + to_string((*allValidMoves)[i]) + " of maximising parent: " +
                to_string(_move) + " has cost: " + to_string(costValue) + "\n");
            if (costValue > bestValue)
            {
                bestValue = costValue;
                //Only set the best move at the root level
                BestMove = (_depth == MaxDepth ? (*allValidMoves)[i] : BestMove);
                printString(std::cout, 3, "New Maximum " + to_string(bestValue) + " move " + to_string(BestMove) + " depth " + to_string(_depth) + "\n");
            }
            
            _alpha = (_alpha >= bestValue) ? _alpha : bestValue;
            if (_beta <= _alpha) 
            {
                printString(std::cout, 2, "Number of valid moves: " + to_string(allValidMoves->size()) + "\n");
                printString(std::cout, 2, to_string(i) + " Pruned branches  b: " + to_string(_beta) + " a: " + to_string(_alpha) + "\n");
                int tempDepth = MaxDepth - _depth;
                GlobalPrunes += 1 /*(double) powl(CurrentBoard->NumCol, tempDepth)*/;
                break;
            }
            
        }
    }
    else
    {
        printString(std::cout, 3, "Minimum player searching...\n");
        bestValue = INF;
        vector<int>* allValidMoves = CurrentBoard->GetAllValidMoves();
        for (int i = 0; i < allValidMoves->size(); i++)
        {
            costValue = AlphaBeta((*allValidMoves)[i], _depth - 1, _alpha, _beta, true, (p == P1_MOVE ? P2_MOVE : P1_MOVE));
            costValue = DepthNormalise(costValue);
            printString(std::cout, 3, "Child " + to_string((*allValidMoves)[i]) + " of minimising parent: " +
                to_string(_move) + " has cost: " + to_string(costValue) + "\n");
            if (costValue < bestValue)
            {
                bestValue = costValue;
                //Only set the best move at the root level
                BestMove = (_depth == MaxDepth ? (*allValidMoves)[i] : BestMove);
                printString(std::cout, 3, "New minimum " + to_string(bestValue) + " move " + to_string(BestMove) + " depth " + to_string(_depth) + "\n");
            }
            
            _beta = (_beta <= bestValue) ? _beta : bestValue;
            if (_beta <= _alpha) 
            {
                printString(std::cout, 2, "Number of valid moves: " + to_string(allValidMoves->size()) + "\n");
                printString(std::cout, 2, to_string(i) + " beta b: " + to_string(_beta) + " a: " + to_string(_alpha) + "\n");
                int tempDepth = MaxDepth - _depth;
                GlobalPrunes += 1 /*(double) powl(CurrentBoard->NumCol, tempDepth)*/;
                break;
            }
            
        }
    }
    printString(std::cout, 3, "Cleaning up stack call at depth: " + to_string(_depth) + "\n");
    
    delete allValidMoves;
    if (!(_depth == MaxDepth && MakingFirstMoveOfGame))
    {
        (*CurrentBoard).UnMakeMove(_move + 1);
    }
    return bestValue;
}

void AlphaBetaAI::SwapTwoElements(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int AlphaBetaAI::GetBestMove()
{
    return BestMove+1;
}

void AlphaBetaAI::Play(Board * _CurrentBoard)
{
    printString(std::cout, 2, "Making a play\n");
    //Copy of board for modifications
    CurrentBoard = _CurrentBoard;;

    //Setup run
    bool MaxPlayer = (player != CurrentBoard->LastMove);
    Move playerMove = (player == P1_MOVE ? P2_MOVE : P1_MOVE);
    MakingFirstMoveOfGame = (CurrentBoard->MoveCol == -1);  //When making first move of the game -> set variable
    printString(std::cout, 2, "MaxPlayer: " + to_string(MaxPlayer) + "\n");
    printString(std::cout, 2, "Player Move: " + to_string(playerMove) + "\n");

    //Undo last move and redo it as minimizing
    int prevCol = CurrentBoard->MoveCol;
    Move lastMove = CurrentBoard->LastMove;
    if (!MakingFirstMoveOfGame)
    {
        CurrentBoard->UnMakeMove(prevCol + 1);
    }
    printString(std::cout, 2, "UnMaking previous play\n");

    //Move to make is self
    BestUtility = AlphaBeta(prevCol, MaxDepth, -9999999, 9999999, MaxPlayer, playerMove);

    //Remake original move
    if (!MakingFirstMoveOfGame)
    {
        CurrentBoard->MakeMove(prevCol + 1, lastMove);
    }

    printString(std::cout,1, "Player 1: " + to_string(player == P1_MOVE) + "\n");
    printString(std::cout,1, "Utility: " + to_string(BestUtility) + "\n");
    printString(std::cout,1, "Explored: " + to_string(NodesExplored) + "\n");
    printString(std::cout,1, "Pruned: " + to_string(GlobalPrunes) + "\n");
}