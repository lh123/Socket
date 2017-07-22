// SocketClient.cpp : 定义控制台应用程序的入口点。
#include <iostream>
#include "../SocketLib/SocketClient.h"

struct Student {
	char name[20];
	int age;
};
int main() {

	SocketClient *client = new SocketClient;
	if (!client->connectHost("127.0.0.1", 10000)) {
		std::cout << "连接失败" << std::endl;
		std::cin.get();
		return 0;
	}
	int num = 0;
	while (true){
		int size = 0;
		client->getData((char *)&size, sizeof(size));
		std::cout << "收到数据包大小" << size << std::endl;
		bool ok = true;
		std::cout << "发送应答" << std::endl;
		client->sendData((char *)&ok, sizeof(ok));
		std::cout << "收到数据" << std::endl;
		Student stu;
		client->getData((char *)&stu, sizeof(stu));
		std::cout << "name:" << stu.name << " age" << stu.age << std::endl;
		getchar();
		if (num++ > 10) {
			break;
		}
		std::cout << "发送应答" << std::endl;
		bool needMore = true;
		client->sendData((char *)&needMore, sizeof(needMore));
	}
	std::cin.get();
	return 0;
}


