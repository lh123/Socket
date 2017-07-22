#include "SocketClient.h"

SocketClient::SocketClient(){
}

SocketClient::SocketClient(SOCKET socket)
{
	mSocket = socket;
}


SocketClient::~SocketClient(){

}

bool SocketClient::connectHost(const char * host, short port) {
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
	addr.sin_addr.S_un.S_addr = inet_addr(host);

	if (connect(mSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		return false;
	}
	return true;
}
