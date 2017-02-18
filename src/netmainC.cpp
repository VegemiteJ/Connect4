#include "ClientSocketSet.h"
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
	ClientSocketSet client = ClientSocketSet("localhost", "23156");
	std::string msg;
	std::getline(std::cin,msg);
	int status;
	char* msg1;

	for(int i = 0; i < 1000; i++) {
		status = client.sendMessage(msg);
		msg1 = client.receiveMessage();
		std::cout << i << ": Status:[" << status << "], msg:[" << msg1 << "]\n" << std::endl;
	}
	return 0;
}