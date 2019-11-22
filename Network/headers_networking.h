
#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>

namespace GameNetwork
{
	std::string socket_address_to_string(SOCKADDR_IN &addr);
}
