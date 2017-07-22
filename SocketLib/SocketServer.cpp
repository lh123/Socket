#include "SocketServer.h"
#include "SocketClient.h"

SocketServer::SocketServer()
{
}


SocketServer::~SocketServer()
{
}

bool SocketServer::listener(short port){
	WORD version = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(version, &wsaData) != 0) {
		return false;
	}

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == SOCKET_ERROR) {
		return false;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(mSocket, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR) {
		return false;
	}
	if(listen(mSocket, 5) == SOCKET_ERROR){
		return false;
	}
	return true;
}

Socket *SocketServer::waitForConnect(SOCKADDR *addr,int *len){
	SOCKET socket = accept(mSocket, addr, len);
	return new SocketClient(socket);
}
