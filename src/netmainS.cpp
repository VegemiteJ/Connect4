#include "ServerSocketSet.h"
#include <string>
#include <iostream>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	ServerSocketSet socket = ServerSocketSet("23156");
	std::cout << "Error Flag:[" << socket.errorFlag << "]" << std::endl;
	char* msg;
	int status;

	for (int i = 0; i < 1000; i++) {
		msg = socket.receiveMessage();
		if (msg!=NULL) {
			std::cout << "MsgRecv:[" << msg << "]" << std::endl;
		} else {
			std::cout << "MsgRecv:[" << "NULL" << "]" << std::endl;
		}
		status = socket.sendMessage(msg);
		std::cout << i << ": ServerStatus: " << status << ", msg: " << msg << std::endl;
	}

	return 0;
}