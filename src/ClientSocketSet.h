#ifndef CLIENTSOCKETSET_H
#define CLIENTSOCKETSET_H

#include <winsock2.h>
#define __USE_W32_SOCKETS
#define USE_SYS_TYPES_FD_SET
#define WIN32_LEAN_AND_MEAN
#include <ws2tcpip.h>
#include <windows.h>
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
    char* recvbuf;
    int recvbuflen;
};


#endif