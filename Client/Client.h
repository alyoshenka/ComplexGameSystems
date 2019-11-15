#pragma once
#include <WinSock2.h>
#include <stdio.h>

#pragma warning(disable:4996)

class client
{
	WORD winsock_version;
	WSADATA winsock_data;

	int address_family;
	int type;
	int protocol;
	SOCKET sock;

	SOCKADDR_IN server_address;

	char message[IDENTIFY_BUFFER_SIZE];

public:
	int initialize_win_sock();
	int initialize_socket();
	int initialize_address();
	int initialize_client();

	int send_message();
	int recieve_message();
	int run_connection(bool try_send, bool try_recieve);

	int part2();
};