#pragma once
#include <WinSock2.h>
#include <stdio.h>

#pragma warning(disable:4996)

#define FAIL -1;
#define PASS 1;

class server
{
	WORD winsock_version;
	WSADATA winsock_data;

	int address_family;
	int type;
	int protocol;
	SOCKET sock;

	SOCKADDR_IN local_address;

	char buffer[IDENTIFY_BUFFER_SIZE];
	int flags;
	SOCKADDR_IN from;
	int from_size;
	int bytes_recieved;

public:

	int initialize_win_sock();
	int initialize_socket();
	int initialize_address();
	int initialize_buffer();
	int initialize_server();

	int run_connection();

	int part2();
};