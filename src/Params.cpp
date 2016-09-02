#include "Params.h"
#include "PrintConsole.h"
#include <string>

Params::Params() : networkGame(false), isServer(false), seenFirstPlayer(false),
	seenPlayers(false), p1(""), p2(""), heuristic1(0), randSwaps1(-1),
	heuristic2(0), randSwaps2(-1),aiParams1(0), idTime1(-1), itrDepth1(-1),
	aiParams2(0), idTime2(-1), itrDepth2(-1), bs(""), of(""), verbosity(-100) {}

void Params::InputSuccess()
{
	if ( (argc == 2) && (string(argv[1]) == "help") ) {
		PrintConsole("./Connect4 (-n [0|1]) [p1] [p2] (player options) (brd state file) (output file name) (-v [verbose level])\n", -1000);
		PrintConsole("Network Game: (-n) followed by 0 if client, 1 if server\n",-1000);
		PrintConsole("Possible Players are:\n", -1000);
		PrintConsole("\tLocal Player \t\t(-lp)\n",-1000);
		PrintConsole("\tNetwork Player \t\t(-np)\n",-1000);
		PrintConsole("\tRandom Player \t\t(-rp)\n",-1000);
		PrintConsole("\tAi Player \t\t(-ai)\n",-1000);

		PrintConsole("\nPlayer Options are:\n",-1000);
		PrintConsole("\tChoose MM or AB ai\t(-mm, -ab)\n",-1000);
		PrintConsole("\tIterative Deepening\t(-id [time])\n",-1000);
		PrintConsole("\tInitial search depth\t(-d [val])\n",-1000);
		
		PrintConsole("\nNode heuristic selection:\n",-1000);
		PrintConsole("\tWinstate\t\t(-ws)\n",-1000);
		PrintConsole("\tConnect3\t\t(-c3)\n",-1000);
		PrintConsole("\tConnect2\t\t(-c2)\n",-1000);
		PrintConsole("\tConnective\t\t(-cprime)\n",-1000);
		PrintConsole("\tNumber of random swaps\t(-rs [val])\n",-1000);
		
		PrintConsole("\nUse a board state\t\t(-bs [path to file])\n",-1000);
		PrintConsole("\nPrint game to output file\t(-of [path])\n",-1000);

		PrintConsole("\nVerbosity Level: 4 For everything, 0 for nothing but raw game\n\t(-v [value])\n",-1000);

		exit(-1);
	}
	if (argc <= 3) {
		PrintConsole("Error: Not enough inputs given. Type ./Connect4 help for usage\n",-1000);
		exit(-1);
	}
}

void Params::ParsePlayer(std::string in)
{
	if ( seenPlayers == true)
	{
		//Error already have 2 players
		PrintConsole("Error: params - already have two players\n",-1000);
		exit(-1);
	}
	if (!seenFirstPlayer) {
		p1 = in;
		seenFirstPlayer = true;
	} else {
		p2 = in;
		seenPlayers = true;
	}
}


void Params::ParseParams(int m_argc, const char** m_argv)
{
	PrintConsole("Num args: " + to_string(m_argc) + "\n", 3);

	argc = m_argc;
	argv = m_argv;
	InputSuccess();

	int ix = 1;
	seenFirstPlayer = false;
	seenPlayers = false;

	while (ix < argc)
	{
		if (string(argv[ix]) == "-n"){
			PrintConsole("-n\n",3);
			//Read next number ix++
			int tempVal = std::stoi(argv[++ix]);
			if (tempVal==0){
				networkGame = false;
			} else if (tempVal == 1) {
				networkGame = true;
			} else {
				PrintConsole("Error: Params - Invalid network specificier",-1000);
				exit(-1);
			}
			PrintConsole("Network Game? "+to_string(networkGame)+"\n",-3);
		}else if (string(argv[ix]) == "lp") {	//lcl player
			PrintConsole("lp\n",3);
			ParsePlayer(argv[ix]);
		}else if (string(argv[ix]) == "np") {	//network player
			PrintConsole("np\n",3);
			ParsePlayer(argv[ix]);
		}else if (string(argv[ix]) == "rp") {	//randome player
			PrintConsole("rp\n",3);
			ParsePlayer(argv[ix]);
		}else if (string(argv[ix]) == "ai") {	//ai player
			PrintConsole("ai\n",3);
			ParsePlayer(argv[ix]);
		}else if (string(argv[ix]) == "-mm") {	//ai option ab or mm
			PrintConsole("-mm\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				aiParams1 &= (0<<1);
			} else if (seenPlayers){
				aiParams2 &= (0<<1);
			} else { 
				PrintConsole("Error: Params - Invalid aiparam ordering",-1000);
				exit(-1);
			}
		}else if (string(argv[ix]) == "-ab") {	//^^
			PrintConsole("-ab\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				aiParams1 |= (1<<1);
			} else if (seenPlayers) {
				aiParams2 |= (1<<1);
			} else { 
				PrintConsole("Error: Params - Invalid aiparam ordering",-1000);
				exit(-1);
			}
		}else if (string(argv[ix]) == "-id") {	//iterative deepening
			PrintConsole("-id\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				aiParams1 |= (1<<0);
			} else if (seenPlayers) {
				aiParams2 |= (1<<0);
			} else { 
				PrintConsole("Error: Params - Invalid aiparam ordering",-1000);
				exit(-1);
			}
			int tempVal = std::stoi(argv[++ix]);
			if (tempVal>0){
				if (seenFirstPlayer && !seenPlayers) {
					idTime1 = tempVal;
				} else if (seenPlayers) {
					idTime2 = tempVal;
				}
			} else  {
				PrintConsole("Error: Params - Invalid idtime value",-1000);
				exit(-1);
			}			
		}else if (string(argv[ix]) == "-d") {	//initial search depth
			PrintConsole("-d\n",3);
			int tempVal = std::stoi(argv[++ix]);
			if (tempVal>0){
				if (seenFirstPlayer && !seenPlayers) {
					itrDepth1 = tempVal;
				} else if (seenPlayers) {
					itrDepth2 = tempVal;
				}
			} else  {
				PrintConsole("Error: Params - Invalid depth value",-1000);
				exit(-1);
			}	
		}else if (string(argv[ix]) == "-ws") {	//winstate heuristic
			PrintConsole("-ws\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				heuristic1 |= (1<<3);
			} else if (seenPlayers) {
				heuristic2 |= (1<<3);
			} else { 
				PrintConsole("Error: Params - Invalid heuristic ordering",-1000);
				exit(-1);
			}
		}else if (string(argv[ix]) == "-c3") {	//connect 3 heuristic
			PrintConsole("-c3\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				heuristic1 |= (1<<2);
			} else if (seenPlayers) {
				heuristic2 |= (1<<2);
			} else { 
				PrintConsole("Error: Params - Invalid heuristic ordering",-1000);
				exit(-1);
			}
		}else if (string(argv[ix]) == "-c2") {	//connect 2 heuristic
			PrintConsole("-c2\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				heuristic1 |= (1<<1);
			} else if (seenPlayers) {
				heuristic2 |= (1<<1);
			} else { 
				PrintConsole("Error: Params - Invalid heuristic ordering",-1000);
				exit(-1);
			}
		}else if (string(argv[ix]) == "-cprime") {	//connectivity heuristic
			PrintConsole("-cprime\n",3);
			if (seenFirstPlayer && !seenPlayers) {
				heuristic1 |= (1<<0);
			} else if (seenPlayers) {
				heuristic2 |= (1<<0);
			} else { 
				PrintConsole("Error: Params - Invalid heuristic ordering",-1000);
				exit(-1);
			}
		}else if (string(argv[ix]) == "-rs") {	//num of rand swaps in discoverChild
			PrintConsole("-rs\n",3);
			int tempVal = std::stoi(argv[++ix]);
			if (tempVal>0){
				if (seenFirstPlayer && !seenPlayers) {
					randSwaps1 = tempVal;
				} else if (seenPlayers) {
					randSwaps2 = tempVal;
				}
			} else  {
				PrintConsole("Error: Params - Invalid randSwap value",-1000);
				exit(-1);
			}	
		}else if (string(argv[ix]) == "-bs") {	//initial board state
			PrintConsole("-bs\n",3);
			bs = argv[++ix];
		}else if (string(argv[ix]) == "-of") {	//output file
			PrintConsole("-of\n",3);
			of = argv[++ix];
		}else if (string(argv[ix]) == "-v") {	//verbose level
			PrintConsole("-v\n",3);
			verbosity = std::stoi(argv[++ix]);
		}else{
			PrintConsole("Unknown param: " + string(argv[ix]) + "\n",3);
		}
		ix++;
	}

	return;
}