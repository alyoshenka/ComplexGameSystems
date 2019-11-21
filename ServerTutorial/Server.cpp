#include "Server.h"

int server::initialize_win_sock()
{
	winsock_version = 0x202;
	winsock_data;

	if (WSAStartup(winsock_version, &winsock_data))
	{
		printf("WSAStartup failed: %d", WSAGetLastError());
		return FAIL;
	}
	return PASS;
}

int server::initialize_socket()
{
	address_family = AF_INET; // IPv4
	type = SOCK_DGRAM; // UDP
	protocol = IPPROTO_UDP;
	sock = socket(address_family, type, protocol);
	if (sock == INVALID_SOCKET)
	{
		printf("socket failed: %d", WSAGetLastError());
		return FAIL;
	}
	return PASS;
}

int server::initialize_address()
{
	local_address.sin_family = AF_INET;
	local_address.sin_port = htons(9999); // host to network short, converts endiannes of executing machine to big-endian
	local_address.sin_addr.S_un.S_addr = inet_addr("10.15.20.16"); // allow sockets to check on all interfaces

	if (bind(sock, (SOCKADDR*)&local_address, sizeof(local_address)) == SOCKET_ERROR)
	{
		printf("bind failed: %d", WSAGetLastError());
		return FAIL;
	}
	return PASS;
}

int server::initialize_buffer()
{
	buffer[IDENTIFY_BUFFER_SIZE];
	flags = 0;
	from_size = sizeof(from);

	return PASS;
}

int server::initialize_server()
{
	if(-1 == initialize_win_sock()
		|| -1 == initialize_socket()
		|| -1 == initialize_address()
		|| -1 == initialize_buffer())
	{
		return FAIL;
	}
	return PASS; 
}

int server::run_connection()
{
	bytes_recieved = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);

	if (bytes_recieved == SOCKET_ERROR)
	{
		printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d", WSAGetLastError());
		return FAIL;
	}
	buffer[bytes_recieved] = 0;
	printf("%d.%d.%d.%d.%d - %s\n",
		from.sin_addr.S_un.S_un_b.s_b1,
		from.sin_addr.S_un.S_un_b.s_b2,
		from.sin_addr.S_un.S_un_b.s_b3,
		from.sin_addr.S_un.S_un_b.s_b4,
		from.sin_port,
		buffer);
	return PASS;
}

int server::part2()
{
	typedef char int8;
	typedef int int32;
	typedef int bool32;

	int8 buffer[IDENTIFY_BUFFER_SIZE];
	int32 player_x = 0;
	int32 player_y = 0;

	bool32 is_running = 1;
	while (is_running)
	{
		// get input packet from player
		int flags = 0;
		SOCKADDR_IN from;
		int from_size = sizeof(from);
		int bytes_recieved = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);
		if (bytes_recieved == SOCKET_ERROR)
		{
			printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d", WSAGetLastError());
			return FAIL;
		}

		char client_input = buffer[0];
		printf("player %d.%d.%d.%d:%d sent data: %c\n",
			from.sin_addr.S_un.S_un_b.s_b1,
			from.sin_addr.S_un.S_un_b.s_b2,
			from.sin_addr.S_un.S_un_b.s_b3,
			from.sin_addr.S_un.S_un_b.s_b4,
			from.sin_port,
			client_input);

		switch (client_input)
		{
		case 'w':
			++player_y;
			break;

		case 'a':
			--player_x;
			break;

		case 's':
			--player_y;
			break;

		case 'd':
			++player_x;
			break;

		case 'q':
			is_running = 0;
			break;

		default:
			printf("unhandled input %c\n", client_input);
			break;
		}

		// create state packet, copy into buffer
		int32 write_index = 0;
		memcpy(&buffer[write_index], &player_x, sizeof(player_x));
		write_index += sizeof(player_x);

		memcpy(&buffer[write_index], &player_y, sizeof(player_y));
		write_index += sizeof(player_y);

		memcpy(&buffer[write_index], &is_running, sizeof(is_running));

		// send back to client
		int buffer_length = sizeof(player_x) + sizeof(player_y) + sizeof(is_running);
		flags = 0;
		SOCKADDR* to = (SOCKADDR*)&from;
		int to_length = sizeof(from);
		if (sendto(sock, buffer, buffer_length, flags, to, to_length) == SOCKET_ERROR) 
		{
			printf("sendto failed: %d", WSAGetLastError());
			return FAIL;
		}

	}
}

