#include "ServerSocketSet.h"
#include <iostream>

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
ServerSocketSet::ServerSocketSet(std::string port) : iResult(0), iSendResult(0)
{
	errorFlag = 0;
    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;
    recvbuflen = DEFAULT_BUFLEN;
    recvbuf = new char[recvbuflen];
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

    const char* PortInUse;

    if (std::stoi(port) < 1000 || std::stoi(port) > 65536) {
        PortInUse = DEFAULT_PORT;
    } else {
        PortInUse = port.c_str();
    }

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, PortInUse, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        errorFlag = 2;
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        errorFlag = 3;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        errorFlag = 4;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        errorFlag = 5;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        errorFlag = 6;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // No longer need server socket
    closesocket(ListenSocket);
}

ServerSocketSet::~ServerSocketSet()
{
}

void ServerSocketSet::exit()
{
    closesocket(ClientSocket);
    WSACleanup();
}

ServerSocketSet::ServerSocketSet( const ServerSocketSet &obj ) {}

//Returns: 0 if successful, any otherwise
//Inputs: Message to send
//Description: Sends a message to the already open client socket.
//	If it fails, returns non-zero, otherwise returns zero if successful
int ServerSocketSet::sendMessage(std::string msg) {
	if(errorFlag!=0)
		return -1;

	char* sendBuf = new char[msg.length() + 1];	//Allocate the send buff
	strcpy_s(sendBuf, msg.length()+1, msg.c_str());
    //std::cout << "Sending msg:[" << sendBuf << "] of length:" << (int)strlen(sendBuf) << std::endl;

	iSendResult = send( ClientSocket, sendBuf, msg.length()+1, 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        delete[] sendBuf;
        WSACleanup();
        return 1;
    } else {
    	printf("Bytes sent: %d\n", iSendResult);
    	delete[] sendBuf;
    	return iSendResult;
    }
}

//Returns: pointer to the received data. Null ptr if fail
//Inputs: none
//Description: Attempts to receive a message.
char* ServerSocketSet::receiveMessage() {
    ZeroMemory( &(recvbuf[0]), DEFAULT_BUFLEN );
    //std::cout << "Called Receive\n";
	char* toBuff = recvbuf;
    //std::cout << "Length of buffer: " << recvbuflen << std::endl;
    iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    std::string msg = std::string(toBuff);
    //std::cout << "iResult:[" << iResult << "], msg:[" << msg << "]" << std::endl;
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
        toBuff = recvbuf;
        return toBuff;
    } else {		//Received zero bytes
    	//Return error
    	return toBuff;
    }

    return toBuff;
}


//Returns: none
//Inputs: none
//Description: Zeros the receive buffer
void ServerSocketSet::zeroBuf() {
	ZeroMemory( &recvbuf, DEFAULT_BUFLEN );
}