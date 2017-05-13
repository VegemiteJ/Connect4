#include "gtest/gtest.h"
/*
#include "Matrix_Tests.h"
#include "Board_Tests.h"
#include "HumanPlayer_Tests.h"
#include "GameStateEvaluator_Tests.h"
*/
#include "AlphaBetaAI_Tests.h"

#include <iostream>

int main(int ac, char* av[])
{
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:TestResult.xml";
    ::testing::InitGoogleTest(&ac, av);

	return RUN_ALL_TESTS();
}