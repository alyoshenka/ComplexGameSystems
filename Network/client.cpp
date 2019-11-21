#include "client.h"

namespace GameNetwork
{
	client::client() : network_connection()
	{

		recipient = (SOCKADDR*)& server_address;
		recipient_length = sizeof(server_address);

		read_index = -1;

		printf("client started\n");
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
		printf("client connected\n");
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
		bytes_received = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)& from, &from_size);
		if (bytes_received == SOCKET_ERROR)
		{
			printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d\n", WSAGetLastError());
			return FAIL;
		}

		// grab data from packet
		read_index = 0;
		memcpy(&data.value, &buffer[read_index], sizeof(&data.value));

		std::cout << "player data value: " << data.value << std::endl;
	}

	address_struct client::get_address() { return address; }

	void client::set_address(address_struct new_address)
	{
		address.a = new_address.a;
		address.b = new_address.b;
		address.c = new_address.c;
		address.d = new_address.d;
	}

	std::string client::get_address_string()
	{
		return std::to_string(address.a) + "." + std::to_string(address.b) 
			+ "." + std::to_string(address.c) + "." + std::to_string(address.d);
	}

	bool client::operator==(client& lhs)
	{
		return address == lhs.get_address();
	}

}

