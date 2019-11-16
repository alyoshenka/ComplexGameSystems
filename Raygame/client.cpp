#include "client.h"

client::client() : network_connection()
{
	address.sin_addr.S_un.S_un_b.s_b1 = 0;
	address.sin_addr.S_un.S_un_b.s_b2 = 0;
	address.sin_addr.S_un.S_un_b.s_b3 = 0;
	address.sin_addr.S_un.S_un_b.s_b4 = 0;

	recipient = (SOCKADDR*)&server_address;
	recipient_length = sizeof(server_address);
}

bool client::initialize_connection()
{
	if (initialize_win_sock() == -1
		|| initialize_socket() == -1
		|| initialize_address() == -1)
	{
		printf("client failed\n");
		return FAIL;
	}
	printf("client started\n");
	return PASS;
}

bool client::run_connection()
{
	// get input
	scanf_s("\n%c", &buffer[0], 1);

	// send to server
	int buffer_length = 1;
	if (sendto(sock, buffer, buffer_length, flags, recipient, recipient_length) == SOCKET_ERROR)
	{
		printf("sendto failed: %d\n", WSAGetLastError());
		return FAIL;
	}

	// wait for reply
	bytes_received = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);
	if (bytes_received == SOCKET_ERROR)
	{
		printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d\n", WSAGetLastError());
		return FAIL;
	}

	// grab data from packet
	read_index = 0;
	memcpy(&data.value, &buffer[read_index], sizeof(&data.value));

	printf("player data value: %d\n", data.value);
}

SOCKADDR_IN client::get_address() { return address; }

void client::set_address(SOCKADDR_IN new_address)
{
	address = new_address;
}

std::string client::get_address_string()
{
	std::string ret = "";
	ret += address.sin_addr.S_un.S_un_b.s_b1;
	ret += ".";
	ret += address.sin_addr.S_un.S_un_b.s_b2;
	ret += ".";
	ret += address.sin_addr.S_un.S_un_b.s_b3;
	ret += ".";
	ret += address.sin_addr.S_un.S_un_b.s_b4;
	return ret;
}

bool client::operator==(client & lhs)
{
	SOCKADDR_IN lhs_address = lhs.get_address();

	return lhs_address.sin_addr.S_un.S_un_b.s_b1 == address.sin_addr.S_un.S_un_b.s_b1
		&& lhs_address.sin_addr.S_un.S_un_b.s_b2 == address.sin_addr.S_un.S_un_b.s_b2
		&& lhs_address.sin_addr.S_un.S_un_b.s_b3 == address.sin_addr.S_un.S_un_b.s_b3
		&& lhs_address.sin_addr.S_un.S_un_b.s_b4 == address.sin_addr.S_un.S_un_b.s_b4;
}
