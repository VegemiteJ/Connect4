#pragma once

#include "AlphaBetaAI.h"
#include "Board.h"
#include "gtest/gtest.h"

TEST(AlphaBetaAITests, InternalDepth0)
{
    Board a = Board(7, 6, 4);
    AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
    ai.CurrentBoard = &a;

    int utility = ai.AlphaBeta(0, 0, 0, 0, true, P1_MOVE);
    EXPECT_EQ(utility, 0);
}

TEST(AlphaBetaAITests, InternalDepth1_Part1)
{
    Board a = Board(7, 6, 4);
    AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
    ai.CurrentBoard = &a;

    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(3, P1_MOVE);

    int utility = ai.AlphaBeta(3, 1, 0, 0, true, P1_MOVE);
    EXPECT_EQ(utility, 1000);
}

TEST(AlphaBetaAITests, InternalDepth1_Part2)
{
    Board a = Board(7, 6, 4);
    AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
    ai.CurrentBoard = &a;

    a.MakeMove(1, P2_MOVE);
    a.MakeMove(2, P2_MOVE);
    a.MakeMove(3, P2_MOVE);

    int utility = ai.AlphaBeta(3, 1, 0, 0, true, P2_MOVE);
    EXPECT_EQ(utility, -1000);

    //Use a 4x3 board 
    //  2 Moves for P1, 1 Move for P2, 1 Move for P1
    a = Board(4, 3, 3);
    ai = AlphaBetaAI(P1_MOVE);
    ai.CurrentBoard = &a;
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);

    utility = ai.AlphaBeta(0, 1, -99999, 99999, true, P2_MOVE);
    int move = ai.GetBestMove();
    cout << "Best Move is: " << move << endl;
    cout << "Utility is: " << utility << endl;
    EXPECT_EQ(move, 2);
    EXPECT_EQ(utility, 999);
    cout << a.ToString();

    ai = AlphaBetaAI(P2_MOVE);
    ai.CurrentBoard = &a;
    utility = ai.AlphaBeta(0, 1, -99999, 99999, false, P2_MOVE);
    move = ai.GetBestMove();
    cout << "Best Move is: " << move << endl;
    cout << "Utility is: " << utility << endl;
    EXPECT_EQ(move, 2);
    EXPECT_EQ(utility, -999);
    cout << a.ToString();
}

TEST(AlphaBetaAITests, InternalDepth2_Part1)
{
    AlphaBetaAI ai;
    Board a;
    int utility[3];
    int move[3];
    int bestMove=0;
    int bestUtility=-100000;

    a = Board(4, 3, 3);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    ai = AlphaBetaAI(P2_MOVE);
    ai.CurrentBoard = &a;

    cout << a.ToString();

    for (int i = 0; i < 3; i++)
    {
        utility[i] = ai.AlphaBeta(i, 2, -99999, 99999, false, P2_MOVE);
        move[i] = i;

        if (utility[i] > bestUtility)
        {
            bestUtility = utility[i];
            bestMove = move[i];
        }
    }
    EXPECT_EQ(bestMove, 2);
    EXPECT_EQ(bestUtility, 0);

    a.MakeMove(bestMove + 1, P2_MOVE);
    cout << a.ToString();
    cout << "Number of nodes explored: " << ai.NodesExplored << endl;
    cout << "Number of nodes pruned: " << ai.GlobalPrunes << endl;
}

TEST(AlphaBetaAITests, InternalDepth2_Part2)
{
    AlphaBetaAI ai;
    Board a;
    int utility[3];
    int move[3];
    int bestMove = 0;
    int bestUtility = -100000;

    a = Board(4, 3, 3);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    ai = AlphaBetaAI(P1_MOVE);
    ai.CurrentBoard = &a;

    cout << a.ToString();

    for (int i = 0; i < 3; i++)
    {
        utility[i] = ai.AlphaBeta(i, 2, -99999, 99999, true, P1_MOVE);
        move[i] = i;

        if (utility[i] > bestUtility)
        {
            bestUtility = utility[i];
            bestMove = move[i];
        }
    }
    EXPECT_EQ(bestMove, 2);
    EXPECT_EQ(bestUtility, 1000);

    a.MakeMove(bestMove + 1, P1_MOVE);
    cout << a.ToString();
    cout << "Number of nodes explored: " << ai.NodesExplored << endl;
    cout << "Number of nodes pruned: " << ai.GlobalPrunes << endl;
}

TEST(AlphaBetaAITests, InternalDepth2_Part3)
{
    AlphaBetaAI ai;
    Board a;
    int utility[3];
    int move[3];
    int bestMove = 0;
    int bestUtility = -100000;

    a = Board(4, 3, 3);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(3, P1_MOVE);
    ai = AlphaBetaAI(P1_MOVE);
    ai.CurrentBoard = &a;

    cout << a.ToString();

    for (int i = 0; i < 3; i++)
    {
        utility[i] = ai.AlphaBeta(i, 8, -99999, 99999, true, P1_MOVE);
        move[i] = i;

        if (utility[i] > bestUtility)
        {
            bestUtility = utility[i];
            bestMove = move[i];
        }
    }
    EXPECT_EQ(bestMove, 0);
    EXPECT_EQ(bestUtility, 1000);

    a.MakeMove(bestMove + 1, P1_MOVE);
    cout << a.ToString();
    cout << "Number of nodes explored: " << ai.NodesExplored << endl;
    cout << "Number of nodes pruned: " << ai.GlobalPrunes << endl;
}

TEST(AlphaBetaAITests, PublicInterface)
{
    Board a = Board(4, 4, 3);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P2_MOVE);
    a.MakeMove(3, P1_MOVE);

    cout << a.ToString();
    AlphaBetaAI ai = AlphaBetaAI(P2_MOVE);
    ai.Play(&a);

    int move = ai.GetBestMove();
    cout << "Best Move: " << move << endl;
    a.MakeMove(move + 1, P2_MOVE);
    cout << a.ToString();

    EXPECT_EQ(move, 2);
}

TEST(AlphaBetaAITests, PublicInterface_2)
{
    Board a = Board(4, 4, 3);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P2_MOVE);

    cout << a.ToString();
    AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
    ai.Play(&a);

    int move = ai.GetBestMove();
    cout << "Best Move: " << move << endl;
    a.MakeMove(move + 1, P1_MOVE);
    cout << a.ToString();

    EXPECT_EQ(move, 2);
}

TEST(AlphaBetaAITests, PublicInterface_3)
{
    Board a = Board(4, 4, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P2_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(4, P2_MOVE);
    a.MakeMove(4, P2_MOVE);
    a.MakeMove(4, P1_MOVE);

    AlphaBetaAI ai = AlphaBetaAI(P2_MOVE);
    cout << a.ToString();
    ai.Play(&a);

    int move = ai.GetBestMove();
    cout << "Best Move: " << move << endl;
    a.MakeMove(move + 1, P2_MOVE);
    cout << a.ToString();
    EXPECT_EQ(move, 0);

    a.MakeMove(2, P1_MOVE);
    cout << a.ToString();
    ai.Play(&a);

    move = ai.GetBestMove();
    cout << "Best Move: " << move << endl;
    a.MakeMove(move + 1, P2_MOVE);
    cout << a.ToString();
    EXPECT_NE(move, 0);
    EXPECT_NE(move, 2);
}