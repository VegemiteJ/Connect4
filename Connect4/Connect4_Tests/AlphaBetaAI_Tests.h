#pragma once

#include "AlphaBetaAI.h"
#include "Board.h"
#include "gtest/gtest.h"

/*
Tests include:
	XChooses 3 in a row with one choice
	XChooses one of 3 in a row with two choices

	XChooses win move with depth of 1

	XChoose no move i.e. one utility on board of 3 symbols

	XIdentifies zero utility on a depth of 1 with opponent in a 3-in a row condition

	X2 win states - depth n, chooses the 'sooner' win state

	XChooses move to stop opponent winning, utility zero
	
	X2 opponent win states, chooses move to stop opponent winning sooner

	Correctly does not choose an invalid move - When all columns are full it terminates search
		With move of -1, utility of the evaluated

*/

TEST(AlphaBetaAITests, Chooses3_One_Choice)
{
    Board a = Board(6, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
	AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
    ai.Play(&a);
    int move = ai.GetBestMove();
    int util = ai.BestUtility;
    EXPECT_EQ(move, 1);
    EXPECT_EQ(util, 49);

	a = Board(6, 6, 4);
	a.MakeMove(4, P2_MOVE);
	a.MakeMove(4, P2_MOVE);
	ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 4);
	EXPECT_EQ(util, -49);
}

TEST(AlphaBetaAITests, Chooses3_Two_Choice)
{
	Board a = Board(6, 6, 4);
	AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(6, P1_MOVE);
	a.MakeMove(6, P1_MOVE);
	ai.Play(&a);
	int move = ai.GetBestMove();
	bool equal = (move == 1 || move == 6);
	int util = ai.BestUtility;
	EXPECT_EQ(equal, true);
	EXPECT_EQ(util, 49);
}

TEST(AlphaBetaAITests, Chooses_Win_Move)
{
	Board a;
	int move, util;
	
	a = Board(6, 6, 4);
	AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 3);
	EXPECT_EQ(util, 999);

	a = Board(6, 6, 4);
	ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 3);
	EXPECT_EQ(util, -999);
}

TEST(AlphaBetaAITests, Zero_Depth_Chooses_None)
{
	Board a;
	int move, util;

	a = Board(6, 6, 4);
	AlphaBetaAI ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 0;
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, INT_MIN);
	EXPECT_EQ(util, 50);

	a = Board(6, 6, 4);
	ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 0;
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, INT_MIN);
	EXPECT_EQ(util, -50);
}

TEST(AlphaBetaAITests, Neutral_State_Identification)
{
	Board a;
	int move, util;

	a = Board(6, 6, 4);
	AlphaBetaAI ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 3);
	EXPECT_EQ(util, 0);

	a = Board(6, 6, 4);
	ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 3);
	EXPECT_EQ(util, 0);
}

TEST(AlphaBetaAITests, Chooses_Sooner_Win_State)
{
	/*
	| _ | _ | _ | _ | _ | _ |
	| _ | X | X | _ | _ | _ |
	| X | X | X | _ | O | _ |

	Tests that this board state, P2 correctly blocks earlier win condition with correct evaluation
		accounting for depth difference

	Optimal next move 1:
	| _ | _ | _ | _ | _ | _ |
	| _ | X | X | _ | _ | _ |
	| X | X | X | O | O | _ |

	2:
	| _ | _ | _ | _ | _ | _ |
	| _ | X | X | X | _ | _ |
	| X | X | X | O | O | _ |

	3:
	| _ | _ | _ | _ | _ | _ |  OR  | _ | _ | _ | _ | _ | _ |
	| _ | X | X | X | O | _ |      | O | X | X | X | _ | _ |
	| X | X | X | O | O | _ |      | X | X | X | O | O | _ | 

	Forced Win 4:
	| _ | _ | _ | _ | _ | _ |  OR  | _ | _ | _ | _ | _ | _ |
	| X | X | X | X | O | _ |      | O | X | X | X | X | _ |
	| X | X | X | O | O | _ |      | X | X | X | O | O | _ |
	*/
	Board a;
	int move, util;

	a = Board(6, 6, 4);
	AlphaBetaAI ai1 = AlphaBetaAI(P1_MOVE);
	ai1.MaxDepth = 5;
	AlphaBetaAI ai2 = AlphaBetaAI(P2_MOVE);
	ai2.MaxDepth = 5;

	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(5, P2_MOVE);

	cout << a.ToString() << endl;

	ai2.Play(&a);
	move = ai2.GetBestMove();
	util = ai2.BestUtility;
	EXPECT_EQ(move, 4);
	EXPECT_EQ(util, 996);
}

TEST(AlphaBetaAITests, Stops_Win_Zero_Util) {
	Board a;
	int move, util;

	AlphaBetaAI ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a = Board(6, 6, 4);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 1);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a = Board(6, 6, 4);
	a.MakeMove(4, P2_MOVE);
	a.MakeMove(4, P2_MOVE);
	a.MakeMove(4, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 4);
	EXPECT_EQ(util, 0);
}

TEST(AlphaBetaAITests, Terminates_Early_On_No_More_Moves) {
	Board a;
	int move, util;

	AlphaBetaAI ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 2, 4);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, INT_MIN);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 2, 4);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, INT_MIN);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 2, 4);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, INT_MIN);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 2, 4);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, INT_MIN);
	EXPECT_EQ(util, 0);
}

TEST(AlphaBetaAITests, Chooses_Only_Valid_Columns) {
	Board a;
	int move, util;

	AlphaBetaAI ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 2, 4);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 2);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 2, 4);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 1);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P1_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 3, 4);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 3);
	EXPECT_EQ(util, 0);

	ai = AlphaBetaAI(P2_MOVE);
	ai.MaxDepth = 1;
	a = Board(2, 3, 4);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	ai.Play(&a);
	move = ai.GetBestMove();
	util = ai.BestUtility;
	EXPECT_EQ(move, 2);
	EXPECT_EQ(util, 0);
}