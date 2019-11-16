#pragma once

#include "network_connection.h"
#include "player_data.h"

#include <string>

class client : network_connection
{
	SOCKADDR_IN address;

	int read_index;

	SOCKADDR* recipient;
	int recipient_length;
	
public:

	player_data data;

	client();

	bool initialize_connection() final;
	bool run_connection() final;

	SOCKADDR_IN get_address();
	void set_address(SOCKADDR_IN new_address);
	std::string get_address_string();

	bool operator == (client &lhs);
};