#ifndef SERVERSOCKETSET_H
#define SERVERSOCKETSET_H

#define USE_SYS_TYPES_FD_SET
#define WIN32_LEAN_AND_MEAN
#define __USE_W32_SOCKETS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string> 

#ifndef DEFAULT_BUFLEN
#define DEFAULT_BUFLEN 512
#endif

#ifndef DEFAULT_PORT
#define DEFAULT_PORT "21356"
#endif

class ServerSocketSet 
{
public:
	explicit ServerSocketSet(std::string port);  //Port to use, valid in range 1000:65535
    ~ServerSocketSet();

    //Returns 0 on success, otherwise any
    int sendMessage(std::string);

    //Returns null ptr on message receive fail, else ptr to the data
    //Must call zeroBuf on completion
    char* receiveMessage(void);
    void zeroBuf(void);
    int errorFlag;    
private:
    
    ServerSocketSet( const ServerSocketSet &obj );
    
	SOCKET ListenSocket;
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