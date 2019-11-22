#include "headers_networking.h"

namespace GameNetwork
{
	std::string GameNetwork::socket_address_to_string(SOCKADDR_IN &addr)
	{
		std::string ret = "";
		ret += addr.sin_addr.S_un.S_un_b.s_b1 + ".";
		ret += addr.sin_addr.S_un.S_un_b.s_b2 + ".";
		ret += addr.sin_addr.S_un.S_un_b.s_b3 + ".";
		ret += addr.sin_addr.S_un.S_un_b.s_b4;
		return ret;
	}
}