#include <iostream>
#include "../SocketLib/SocketServer.h"

struct Student {
	char name[20];
	int age;
};
int main()
{
	Student data;
	memcpy(data.name, "Name", sizeof("Name"));
	data.age = 22;
	SocketServer *server = new SocketServer;
	if (!server->listener(10000)) {
		std::cout << "监听10000端口失败" << std::endl;
		return 0;
	}
	SOCKADDR_IN in;
	int len = sizeof(in);
	while (true) {
		std::cout << "等待连接" << std::endl;
		Socket *client = server->waitForConnect((SOCKADDR *)&in, &len);
		while (true)
		{
			int size = sizeof(Student);
			std::cout << "发送数据包大小" << size << std::endl;
			client->sendData((char *)&size, sizeof(size));
			bool ok = false;
			client->getData((char *)&ok, sizeof(ok));
			std::cout << "收到应答" << ok << std::endl;
			if (!ok) {
				break;
			}
			std::cout << "发送数据" << std::endl;
			client->sendData((char *)&data, sizeof(data));
			bool needMore = false;
			std::cout << "等待客户端应答" << std::endl;
			client->getData((char *)&needMore, sizeof(needMore));
			if (!needMore) {
				std::cout << "收到停止信号" << ok << std::endl;
				break;
			}
		}
		delete client;
	}
	getchar();
	return 0;
}

