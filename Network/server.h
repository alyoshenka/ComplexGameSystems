#pragma once

#include "client.h"

namespace GameNetwork
{
	class server : network_connection
	{
		int write_index;

		int current_player_count;

		bool bind_socket();

		
		player* add_new_player(address_struct new_address);

	public:

		server();

		bool initialize_connection() final;
		bool run_connection() final;
	};
}

