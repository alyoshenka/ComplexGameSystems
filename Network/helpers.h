#pragma once

#include <WinSock2.h>
#include <iostream>
#include <string>

namespace Network
{
	struct address_struct
	{
		int a, b, c, d;
		
	public:
		address_struct();

		bool operator == (address_struct lhs);
	};

	std::string socket_address_to_string(SOCKADDR_IN &addr);
	address_struct char_to_address(char* addr_str);
}
