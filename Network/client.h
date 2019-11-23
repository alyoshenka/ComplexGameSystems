#pragma once

#include "network_connection.h"
#include "helpers.h"

namespace GameNetwork
{
	class client : network_connection
	{
		address_struct address;

		int read_index;

		SOCKADDR* recipient;
		int recipient_length;

	public:

		client();

		bool initialize_connection() final;
		bool run_connection() final;

		address_struct get_address();
		void set_address(address_struct new_address);

		bool operator == (client& lhs);

		game* get_game();
	};
}
