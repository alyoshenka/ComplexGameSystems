#include "network_connection.h"

namespace GameNetwork
{
	bool network_connection::initialize_win_sock()
	{
		winsock_version = 0x202;
		winsock_data;

		if (WSAStartup(winsock_version, &winsock_data))
		{
			printf("WSAStartup failed: %d\n", WSAGetLastError());
			return FAIL;
		}
		return PASS;
	}

	bool network_connection::initialize_socket()
	{
		address_family = AF_INET; // IPv4
		type = SOCK_DGRAM; // UDP
		protocol = IPPROTO_UDP;
		sock = socket(address_family, type, protocol);
		if (sock == INVALID_SOCKET)
		{
			printf("socket failed: %d\n", WSAGetLastError());
			return FAIL;
		}
		return PASS;
	}

	bool network_connection::initialize_address()
	{
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(port); // host to network short, converts endiannes of executing machine to big-endian
		server_address.sin_addr.S_un.S_addr = inet_addr(server_string); // allow sockets to check on all interfaces

		return PASS;
	}

	network_connection::network_connection()
	{
		server_string = "192.168.0.9";

		flags = 0;
		from_size = sizeof(from);
	}
}


