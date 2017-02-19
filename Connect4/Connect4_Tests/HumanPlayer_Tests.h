#pragma once

#include "gtest/gtest.h"
#include "Board.h"
#include "HumanPlayer.h"

#include <iostream>

TEST(HumanPlayerTests, Construction)
{
    Board* a = new Board(4, 4);
    HumanPlayer p = HumanPlayer(P1_MOVE);
    EXPECT_EQ(p.position, P1_MOVE);
}