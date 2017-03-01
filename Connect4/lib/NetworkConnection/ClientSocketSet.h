#ifndef CLIENTSOCKETSET_H
#define CLIENTSOCKETSET_H

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

class ClientSocketSet {
public:
    //Attempt to initialise new socket connecting to <addr,destPort>
	ClientSocketSet(std::string addr, std::string destPort);

    //Delete recvbuf
    ~ClientSocketSet();

    //Copy constructor - Not a valid call ever
    ClientSocketSet(const ClientSocketSet &obj);

    //Assumes socket established and connection works. Send msg through socket
    //  Returns the number of bytes sent
	int sendMessage(std::string msg);

    //Receive message into char array
	char* receiveMessage(void);

    //Zero the receive buffer.
	void zeroMemory(void);

    //Error flag for windows socket status messages. Many possible socket errors 
    //  but value is 0 on success. For all errors see:
    //https://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx
    int errorFlag;
private:

    //Windows socket requirements
	SOCKET ClientSocket;
    struct addrinfo *result;
    struct addrinfo hints;
    WSADATA wsaData;

    //Message send and receive details
    int iResult;        //Number of bytes received
    int iSendResult;    //Number of bytes sent
    char* recvbuf;
    int recvbuflen;
};


#endif