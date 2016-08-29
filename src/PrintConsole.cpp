#include "PrintConsole.h"
#include "consts.h"

void PrintConsole(std::string msg, int targetVerbose)
{
	if (verbose > targetVerbose)
		std::cout << msg;
}