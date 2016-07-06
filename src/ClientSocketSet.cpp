#include "ClientSocketSet.h"
#include <iostream>

ClientSocketSet::ClientSocketSet(std::string addr, std::string destPort) {
	SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    int recvbuflen = DEFAULT_BUFLEN;
    errorFlag = 0;

    const char* host = addr.c_str();
    const char* port = destPort.c_str();
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        errorFlag = 1;
        return;
    }

	ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(host, port, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        errorFlag = 2;
        return;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ClientSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ClientSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            errorFlag = 3;
            return;
        }

        // Connect to server.
        iResult = connect( ClientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ClientSocket);
            ClientSocket = INVALID_SOCKET;
            errorFlag = 4;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ClientSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        errorFlag = 5;
        return;
    }
}

int ClientSocketSet::sendMessage(std::string msg) {
	const char* sendbuf = msg.c_str();

    // Send an initial buffer
    std::cout << "Sending msg:[" << sendbuf << "] of length:" << (int)strlen(sendbuf) << std::endl;
    iResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        errorFlag = 5;
        return 0;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }

    //return number of bytes sent
    return (int)strlen(sendbuf);
}

char* ClientSocketSet::receiveMessage(void) {
    // Receive until the peer closes the connection
    char* returnVal = &recvbuf[0];
    iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    if ( iResult > 0 ){
        printf("Bytes received: %d\n", iResult);
    }
    else if ( iResult == 0 ){
        printf("Connection closed\n");
        returnVal = NULL;
    } else {
    	returnVal = NULL;
    }

    return returnVal;
}

void ClientSocketSet::zeroMemory(void) {
    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
}
