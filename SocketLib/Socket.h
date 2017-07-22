#pragma once
#include <WinSock2.h>
class Socket
{
public:
	const static int BUFFER_SIZE = 1024;
	virtual bool sendData(const char *data, unsigned int size);
	virtual bool getData(char *data, unsigned int size);
	virtual void close();
protected:
	SOCKET mSocket;
	char mSendBuffer[BUFFER_SIZE];
	char mRecBuffer[BUFFER_SIZE];
};

