#ifndef CLIENTSOCKETSET_H
#define CLIENTSOCKETSET_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string> 

#ifndef DEFAULT_BUFLEN
#define DEFAULT_BUFLEN 512
#endif

class ClientSocketSet {
public:
	ClientSocketSet(std::string addr, std::string destPort);
	int sendMessage(std::string msg);
	char* receiveMessage(void);
	void zeroMemory(void);

private:
	int errorFlag;

	SOCKET ClientSocket;

    struct addrinfo *result;
    struct addrinfo hints;

    WSADATA wsaData;
    int iResult;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen;
};


#endif