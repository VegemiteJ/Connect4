#ifndef SERVERSOCKETSET_H
#define SERVERSOCKETSET_H

#define DEFAULT_BUFLEN 512

class ServerSocketSet 
{
public:
	ServerSocketSet();



private:
	SOCKET ListenSocket;
	SOCKET ClientSocket;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    WSADATA wsaData;
    int iResult;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen;

};
#endif