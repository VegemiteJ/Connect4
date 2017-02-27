// Connect4Runner.cpp : Defines the entry point for the console application.
#include "Connect4.cpp"

int main(int argc, char* argv[])
{
    int debugLvl = 0;
    if (argc == 2)
    {
        debugLvl = stoi(argv[1]);
    }

    return Run(debugLvl);
}