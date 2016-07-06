#include "ClientSocketSet.h"
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
	ClientSocketSet client = ClientSocketSet("localhost", "23156");
	std::string msg;
	std::getline(std::cin,msg);
	int status = client.sendMessage(msg);

	std::cout << "Status:[" << status << "]" << std::endl;
	return 0;
}