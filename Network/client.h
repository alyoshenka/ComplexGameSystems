#pragma once

#include "network_connection.h"
#include "player_data.h"
#include "helpers.h"

#include <string>

namespace Network
{
	class client : network_connection
	{
		address_struct address;

		int read_index;

		SOCKADDR* recipient;
		int recipient_length;

	public:

		player_data data;

		client();

		bool initialize_connection() final;
		bool run_connection() final;

		address_struct get_address();
		void set_address(address_struct new_address);
		std::string get_address_string();

		bool operator == (client& lhs);
	};
}
