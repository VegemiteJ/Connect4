// Connect4Runner.cpp : Defines the entry point for the console application.
#include "Connect4.cpp"

int main(int argc, char* argv[])
{
    int debugLvl = 0;
    int port = 21356;
    if (argc >= 2)
    {
        debugLvl = stoi(argv[1]);
    }
    if (argc == 3)
    {
        port = stoi(argv[2]);
    }

    return Run(debugLvl, port);
}