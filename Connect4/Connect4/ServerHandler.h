#pragma once

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
#define DEFAULT_PORT 52143
#endif

#include <string>

class ServerHandler
{
private:
    SOCKET ListenSocket;
    SOCKET ClientSocket;

    struct addrinfo *result;
    struct addrinfo hints;

    WSADATA wsaData;
    int iResult;
    int iSendResult;
    char* recvbuf;
    int recvbuflen;

public:
    ServerHandler() {}
    ServerHandler(int port);
    ~ServerHandler();

    void BlockingWaitForConnection();

    bool SendMsg(std::string msg);
    std::string ReceiveMsg(int timeout);

    int ErrorFlag;
};