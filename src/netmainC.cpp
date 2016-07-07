#include "ClientSocketSet.h"
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
	ClientSocketSet client = ClientSocketSet("localhost", "23156");
	std::string msg;
	std::getline(std::cin,msg);
	int status = client.sendMessage(msg);
	char* msg1 = client.receiveMessage();

	std::cout << "Status:[" << status << "], msg:[" << msg1 << "]" << std::endl;
	return 0;
}