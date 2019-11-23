#include "client.h"
#include <cassert>

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

		address_struct player_address
		(
			from.sin_addr.S_un.S_un_b.s_b1,
			from.sin_addr.S_un.S_un_b.s_b2,
			from.sin_addr.S_un.S_un_b.s_b3,
			from.sin_addr.S_un.S_un_b.s_b4
		);

		player * player_to_update = app->find_player(player_address);
		if(nullptr == player_to_update)
		{
			std::cout << "could not update player -> player " << player_address.a << "." << player_address.b << "." << player_address.c << "." << player_address.d << " not found " << std::endl;
			return FAIL;
		}

		// grab data from packet
		read_index = 0;
		memcpy(&player_to_update->pos, &buffer[read_index], sizeof(&(player_to_update->pos)));

		std::cout << "player data value: (" << player_to_update->pos.x << ", " << player_to_update->pos.y << ")" << std::endl;

		return PASS;
	}

	address_struct client::get_address() { return address; }

	void client::set_address(address_struct new_address)
	{
		address.a = new_address.a;
		address.b = new_address.b;
		address.c = new_address.c;
		address.d = new_address.d;
	}

	bool client::operator==(client& lhs)
	{
		return address == lhs.get_address();
	}

	game * client::get_game()
	{
		return app;
	}

}

