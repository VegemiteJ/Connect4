#include "ServerSocketSet.h"
#include <iostream>


int main(int argc, char const *argv[])
{
	ServerSocketSet socket = ServerSocketSet("21456");
	char* msg = socket.receiveMessage();
	if (msg!=NULL) {
		std::cout << "MsgRecv:[" << msg << "]" << std::endl;
	}
	return 0;
}