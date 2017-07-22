#include "Socket.h"

bool Socket::sendData(const char * data, unsigned int size) {
	int sendSize = 0;
	const char *p = data;
	while (sendSize < size) {
		memset(mSendBuffer, 0, sizeof(mSendBuffer));
		int csize = 0;//每次发送的数据量
		if (size - sendSize > sizeof(mSendBuffer)) {
			csize = sizeof(mSendBuffer);
		} else {
			csize = size - sendSize;
		}
		memcpy(mSendBuffer, p, csize);
		csize = send(mSocket, mSendBuffer, csize, 0);
		if (csize < 0) {
			return false;
		}
		p += csize;
		sendSize += csize;
	}
	return true;
}

bool Socket::getData(char * data, unsigned int size) {
	int recSize = 0;
	char *p = data;
	while (recSize < size) {
		memset(mRecBuffer, 0, sizeof(mRecBuffer));
		int csize = 0;
		if (size - recSize > sizeof(mRecBuffer)) {
			csize = sizeof(mRecBuffer);
		} else {
			csize = size - recSize;
		}
		csize = recv(mSocket, mRecBuffer, csize, 0);
		if (csize < 0 || recSize + csize >size) {
			return false;
		}
		memcpy(p, mRecBuffer, csize);
		p += csize;
		recSize += csize;
	}
	return true;
}

void Socket::close()
{
	WSACleanup();
}
