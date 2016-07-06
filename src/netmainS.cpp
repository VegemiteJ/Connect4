#include "ServerSocketSet.h"
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
	ServerSocketSet socket = ServerSocketSet("23156");
	std::cout << "Error Flag:[" << socket.errorFlag << "]" << std::endl;
	char* msg = socket.receiveMessage();
	if (msg!=NULL) {
		std::cout << "MsgRecv:[" << msg << "]" << std::endl;
	} else {
		std::cout << "MsgRecv:[" << "NULL" << "]" << std::endl;
	}
	return 0;
}