#include "ServerSocketSet.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


//Error Messages
//----------------------------------------------
//	0: None
//	1: WSAStartup error
//	2: Server addr and port resolve failed
//	3: Server Connection socket creation fail
//	4: Binding socket
//	5: Listening on socket failed


//Inputs: Port number to attempt assign on. Can fail with port bind exception
//Returns: none
//Description: Sets up TCP connection, leaves open awaiting new message
ServerSocketSet::ServerSocketSet(int port) {
	int errorFlag = 0;
    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;

    result = NULL;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        errorFlag = 1;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        errorFlag = 2;
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        errorFlag = 3;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        errorFlag = 4;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        errorFlag = 5;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        errorFlag = 6;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);
}


//Returns: 0 if successful, any otherwise
//Inputs: Message to send
//Description: Sends a message to the already open client socket.
//	If it fails, returns non-zero, otherwise returns zero if successful
int ServerSocketSet::sendMessage(std::string msg) {

	if(errorFlag!=0)
		return -1;

	char* sendBuf = new char[msg.length()](msg);	//Allocate the send buff

	iSendResult = send( ClientSocket, sendBuf, msg.length());
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    } else {
    	printf("Bytes sent: %d\n", iSendResult);
    	free(sendBuf);
    	return 0;
    }
}

//Returns: pointer to the received data. Null ptr if fail
//Inputs: none
//Description: Attempts to receive a message.
char* ServerSocketSet::receiveMessage() {
	char* toBuff = NULL;
    iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
        toBuff = *recvbuf;
        return toBuff;
    } else {		//Received zero bytes
    	//Return error
    	return toBuff;
    }
}


//Returns: none
//Inputs: none
//Description: Zeros the receive buffer
void zeroBuf() {
	ZeroMemory( &recvbuf, DEFAULT_BUFLEN );
}