#pragma once

#include "IterativeDeepenAI.h"
#include "Board.h"
#include "gtest/gtest.h"

TEST(IterativeDeepenAITests, Stop_Crash_On_Specific_Board) {
	Board a = Board(4, 4, 4);
	IterativeDeepenAI ai(P2_MOVE);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(4, P1_MOVE);
	a.MakeMove(4, P2_MOVE);
	a.MakeMove(4, P1_MOVE);
	a.MakeMove(4, P1_MOVE);
	cout << a.ToString() << endl;
	ai.Play(&a);
	int move = ai.GetBestMove();
	int util = ai.BestUtility;
	cout << "Chosen Move: " << move << endl;
	cout << "Util: " << util << endl;
}