#pragma once

#include "Player.h"
#include "Board.h"
#include "GameStateEvaluator.h"

#include <random>
#include <functional>

#define INF 999999;

class AlphaBetaAI : public Player
{
public:
	int BestUtility;
	size_t NodesExplored;
	AlphaBetaAI(Move _p);
	void Reset();
	
	int GetBestMove();
	void Play(Board* _CurrentBoard);

	int MaxDepth;

	long GlobalPrunes;
private:
    AlphaBetaAI();

    std::uniform_int_distribution<int> distribution;
    std::default_random_engine generator;
    std::function<int()> dice;

    GameStateEvaluator gse;

    Move player;
    Board* CurrentBoard;
    bool MakingFirstMoveOfGame;
    
    /// <summary>
    /// Scale the absolute value of value upwards
    ///	Returns modified value
    ///	e.g. Value 950 becomes 951, -950 becomes -951
    /// </summary>
    /// <param name="value">The value.</param>
    /// <returns></returns>
    int DepthNormalise(int value);
    
    /// <summary>
    /// Minimax search with alpha beta: terminates at given depth
    /// </summary>
    /// <param name="_move">The move.</param>
    /// <param name="_depth">The depth.</param>
    /// <param name="_alpha">The alpha.</param>
    /// <param name="_beta">The beta.</param>
    /// <param name="_maxPlayer">if set to <c>true</c> [maximum player].</param>
    /// <returns></returns>
    //int AlphaBeta(int _move, int _depth, int _alpha, int _beta, bool _maxPlayer, Move p);
	int AlphaBeta(int _depth, int _alpha, int _beta, bool _maxPlayer);

    void SwapTwoElements(int &a, int &b);

    #pragma region GoogleTests
    #include "gtest/gtest_prod.h"
    #pragma endregion
};