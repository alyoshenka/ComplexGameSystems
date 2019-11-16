#pragma once

#include <WinSock2.h>
#include <stdio.h>
#include <iostream>

#pragma warning(disable:4996);

#define FAIL false;
#define PASS true;

class network_connection
{
protected:

	const int port = 9999;
	const char* server_string;

	WORD winsock_version;
	WSADATA winsock_data;

	int address_family;
	int type;
	int protocol;
	SOCKET sock;

	SOCKADDR_IN server_address;

	char message[IDENTIFY_BUFFER_SIZE];
	char buffer[IDENTIFY_BUFFER_SIZE];
	int flags;
	SOCKADDR_IN from;
	int from_size;
	int bytes_received;

	network_connection();

	bool initialize_win_sock();
	bool initialize_socket();
	bool initialize_address();

public:

	virtual bool initialize_connection() = 0;
	virtual bool run_connection() = 0;
};
