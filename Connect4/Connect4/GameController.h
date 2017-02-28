#pragma once

#include "Board.h"
#include "Player.h"

class GameController
{
private:    
    Player* P1;
    Player* P2;

    bool NetworkedGame;
    bool P1IsNetworked;
    int Port;

    int numMoves;
    int terminatingMoveCount;
    Board* BoardEntity;

    Move RunMove(bool p1);

    GameController();

    void UpdateNetworkedPlayer(bool p1);

public:
    GameController(Player* _p1, Player* _p2, bool _NetworkGame, int _port);

    Move PlayGame();
};