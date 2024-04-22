#include "Client.h"

ClientC::ClientC()
{
	this->addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->addr.sin_port = htons(DEFAULT_PORT);
	this->addr.sin_family = AF_INET;
	this->sizeofaddr = sizeof(addr);
}

SOCKET Connection;

void ClientHandler() {
	char msg[256];
	while (true) {
		recv(Connection, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}

int ClientC::ClientConnection() {
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	char msg1[256];
	while (true) {
		std::cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}