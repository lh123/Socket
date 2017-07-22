#pragma once
#include "Socket.h"

class SocketClient : public Socket
{
public:
	SocketClient();
	SocketClient(SOCKET socket);
	~SocketClient();

	bool connectHost(const char *host, short port);
};

