#pragma once
#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#define DEFAULT_PORT 7777
#define DEFAULT_BUFLEN 1024

class ClientC {
	SOCKADDR_IN addr;
	int sizeofaddr;

public:
	ClientC();
	int ClientConnection();
		
};
