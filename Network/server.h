#pragma once

#include "network_connection.h"
#include "client.h"


namespace Network
{
	class server : network_connection
	{
		const static int MAX_PLAYER_COUNT = 5;

		int write_index;

		client* players[MAX_PLAYER_COUNT];
		int current_player_count;

		bool bind_socket();

		bool check_if_new_player(address_struct queried_address);
		bool check_address_equality(SOCKADDR_IN addr_1, SOCKADDR_IN addr_2);
		client* add_new_player(address_struct new_address);

	public:

		server();

		bool initialize_connection() final;
		bool run_connection() final;

		client* find_player(address_struct player_address);
	};
}

