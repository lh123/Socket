#pragma once
#include "Socket.h"
class SocketServer : public Socket
{
public:
	SocketServer();
	~SocketServer();

	bool listener(short port);

	Socket *waitForConnect(SOCKADDR *addr, int *len);
};

