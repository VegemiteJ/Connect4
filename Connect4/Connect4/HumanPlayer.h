#pragma once

#include "Player.h"

class HumanPlayer : Player
{
private:

    bool CheckValidMove(vector<int>* possibilities, int selected);

public:
    int position;

    HumanPlayer();
    HumanPlayer(int _position);

    int GetBestMove();
    void Play(Board* CurrentBoard);
};