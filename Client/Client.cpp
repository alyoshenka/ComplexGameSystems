#include "Client.h"

int client::initialize_win_sock()
{
	winsock_version = 0x202;
	winsock_data;

	if (WSAStartup(winsock_version, &winsock_data))
	{
		printf("WSAStartup failed: %d", WSAGetLastError());
		return -1;
	}
	return 0;
}

int client::initialize_socket()
{
	address_family = AF_INET; // IPv4
	type = SOCK_DGRAM; // UDP
	protocol = IPPROTO_UDP;
	sock = socket(address_family, type, protocol);
	if (sock == INVALID_SOCKET)
	{
		printf("socket failed: %d", WSAGetLastError());
		return -1;
	}
	return 0;
}

int client::initialize_address()
{
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9999);
	server_address.sin_addr.S_un.S_addr = inet_addr("10.15.20.16");
	return 0;
}

int client::initialize_client()
{
	if(-1 == initialize_win_sock()
		|| -1 == initialize_socket()
		|| -1 == initialize_address()) { return -1; }
	else { return 0; }
}

int client::send_message()
{
	gets_s(message, IDENTIFY_BUFFER_SIZE);

	int flags = 0;
	if (sendto(sock, message, strlen(message), flags, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		printf("sendto failed: %d", WSAGetLastError());
		return -1;
	}

	return 0;
}

int client::recieve_message()
{
	return 0;
}

int client::run_connection(bool try_send, bool try_recieve)
{
	if (try_recieve && recieve_message() == -1) { return -1; }
	if (try_send && send_message() == -1) { return -1; }
	return 0;
}

int client::part2()
{
	typedef char int8;
	typedef int int32;
	typedef int bool32;

	int8 buffer[IDENTIFY_BUFFER_SIZE];
	int32 player_x = 0;
	int32 player_y = 0;

	printf("type w, a, s, or do to move, q to quit\n");
	
	bool32 is_running = 1;
	while (is_running)
	{
		// get input
		scanf_s("\n%c", &buffer[0], 1);

		// send to server
		int buffer_length = 1;
		int flags = 0;
		SOCKADDR* to = (SOCKADDR*)&server_address;
		int to_length = sizeof(server_address);
		if (sendto(sock, buffer, buffer_length, flags, to, to_length) == SOCKET_ERROR)
		{
			printf("sendto failed: %d", WSAGetLastError());
			return -1;
		}

		// wait for reply
		flags = 0;
		SOCKADDR_IN from;
		int from_size = sizeof(from);
		int bytes_received = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);
		if (bytes_received == SOCKET_ERROR)
		{
			printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d", WSAGetLastError());
			break;
		}

		// grab data from packet
		int32 read_index = 0;
		memcpy(&player_x, &buffer[read_index], sizeof(player_x));
		read_index += sizeof(player_x);

		memcpy(&player_y, &buffer[read_index], sizeof(player_y));
		read_index += sizeof(player_y);

		memcpy(&is_running, &buffer[read_index], sizeof(is_running));

		printf("x: %d, y: %d, is_running: %s\n", player_x, player_y, is_running == 1 ? "true" : "false");
	}
}
