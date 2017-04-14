#include "ServerHandler.h"
#include "DebugLogger.h"

ServerHandler::ServerHandler(int port) : iResult(0), iSendResult(0)
{
    ErrorFlag = 0;
    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;
    recvbuflen = DEFAULT_BUFLEN;
    recvbuf = new char[recvbuflen];
    result = NULL;

    //Initialise Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printString(std::cout, 0, "WSAStartup failed with error: " + to_string(iResult) + "\n");
        ErrorFlag = 1;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    const char* PortInUse;

    if (port < 1000 || port > 65536) {
        PortInUse = to_string(DEFAULT_PORT).c_str();
    }
    else {
        PortInUse = to_string(port).c_str();
    }

    //Resolve server address and port
    iResult = getaddrinfo(NULL, PortInUse, &hints, &result);
    if (iResult != 0)
    {
        printString(std::cout, 0, "Getaddrinfo failed with error: " + to_string(iResult) + "\n");
        ErrorFlag = 2;
        WSACleanup();
        return;
    }

    //Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        printString(std::cout, 0, "Socket failed with error: " + to_string(WSAGetLastError()) + "\n");
        ErrorFlag = 3;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    //Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printString(std::cout, 0, "Bind failed with error: " + to_string(WSAGetLastError()) + "\n");
        ErrorFlag = 4;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    //Prepare for listen
    freeaddrinfo(result);

}

ServerHandler::~ServerHandler()
{
}

void ServerHandler::BlockingWaitForConnection()
{
    //Start listening
    printString(std::cout, 0, "Waiting for connection from user...\n");
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
        printString(std::cout, 0, "Listen failed with error: " + to_string(WSAGetLastError()) + "\n");

    //Accept new socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (iResult == SOCKET_ERROR)
        printString(std::cout, 0, "Accept failed with error: " + to_string(WSAGetLastError()) + "\n");

    // No longer need server socket
    closesocket(ListenSocket);
    printString(std::cout, 0, "Received connection\n");
}

bool ServerHandler::SendMsg(std::string msg)
{
    char* sendBuf = new char[msg.length() + 1];	//Allocate the send buff
    strcpy_s(sendBuf, msg.length() + 1, msg.c_str());

    printString(std::cout, 0, "Sending Message: [" + string(sendBuf) + "] of length " + to_string(strlen(sendBuf)) + "\n");

    iSendResult = send(ClientSocket, sendBuf, msg.length() + 1, 0);
    if (iSendResult == SOCKET_ERROR) {
        printString(std::cout, 0, "Send failed with error: " + to_string(WSAGetLastError()) + "\n");
        closesocket(ClientSocket);
        delete[] sendBuf;
        WSACleanup();
        return false;
    }
    else {
        delete[] sendBuf;
        return true;
    }
}

std::string ServerHandler::ReceiveMsg(int timeout)
{
    ZeroMemory(&(recvbuf[0]), DEFAULT_BUFLEN);

    iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    char* toBuff = recvbuf;

    std::string msg = std::string(toBuff);
    if (iResult > 0) {
        return msg;
    }
    return nullptr;
}
