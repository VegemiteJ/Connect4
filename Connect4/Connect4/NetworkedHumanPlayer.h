#pragma once

#include "Board.h"
#include "HumanPlayer.h"

class NetworkedHumanPlayer : public Player
{
private:
public:
    NetworkedHumanPlayer(Move _p);

    void Play(Board* _CurrentBoard);
    int GetBestMove();
};