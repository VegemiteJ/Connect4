// Connect4.cpp : Defines the entry point for the console application.

#include "Player.h"
#include "HumanPlayer.h"
#include "NetworkedHumanPlayer.h"
#include "AlphaBetaAI.h"
#include "IterativeDeepenAI.h"
#include "GameController.h"

#include "DebugLogger.h"

#include<iostream>

using namespace std;

int Run(int debugLvl, int port)
{
    //Player* p1 = new NetworkedHumanPlayer(P1_MOVE);
	//Player* p1 = new HumanPlayer(P1_MOVE);
    Player* p1 = new IterativeDeepenAI(P1_MOVE, 6);
    Player* p2 = new IterativeDeepenAI(P2_MOVE, 6);
	/*
	auto debugAI = new AlphaBetaAI(P2_MOVE);
	debugAI->MaxDepth = 6;
	Player* p2 = debugAI;
	*/
    //DEBUG_LVL = debugLvl;
    GameController gameRunner = GameController(p1, p2, 4, 4, false, port);

    Move winner = gameRunner.PlayGame();
    string winnerStr = (winner == P1_MOVE ? "P1" : (winner == P2_MOVE ? "P2" : "DRAW"));
    cout << "Winner was: " << winnerStr << endl;
	
    delete p1;
    delete p2;
    
    return winner;
}