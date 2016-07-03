#ifndef SERVERSOCKETSET_H
#define SERVERSOCKETSET_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512

class ServerSocketSet 
{
public:
	ServerSocketSet(int port);  //Port to use, valid in range 1000:65535

    //Returns 0 on success, otherwiseany
    int sendMessage(std::string)

    //Returns null ptr on message receive fail, else ptr to the data
    //Must call zeroBuf on completion
    char* receiveMessage(void);
    void zeroBuf(void);

private:
    int errorFlag;

	SOCKET ListenSocket;
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