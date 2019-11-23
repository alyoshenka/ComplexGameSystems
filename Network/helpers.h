#pragma once

#include <WinSock2.h>
#include <iostream>
#include <string>

namespace GameNetwork
{

#define MAX_PLAYER_COUNT 5

	struct address_struct
	{
		int a, b, c, d;
		
	public:
		address_struct();
		address_struct(int _a, int _b, int _c, int _d);

		bool operator == (address_struct lhs);
		std::string to_string();
	};

	bool check_address_equality(SOCKADDR_IN addr_1, SOCKADDR_IN addr_2);
	std::string socket_address_to_string(SOCKADDR_IN &addr);
	address_struct char_to_address(char* addr_char);
}
