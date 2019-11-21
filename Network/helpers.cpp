#include "helpers.h"

namespace Network
{
	std::string Network::socket_address_to_string(SOCKADDR_IN &addr)
	{
		std::string ret = "";
		ret += addr.sin_addr.S_un.S_un_b.s_b1 + ".";
		ret += addr.sin_addr.S_un.S_un_b.s_b2 + ".";
		ret += addr.sin_addr.S_un.S_un_b.s_b3 + ".";
		ret += addr.sin_addr.S_un.S_un_b.s_b4;
		return ret;
	}

	address_struct char_to_address(char* addr_char)
	{
		std::string addr_str = std::string(addr_char);
		int idx1 = addr_str.find(".");
		int idx2 = addr_str.find(".", idx1 + 1);
		int idx3 = addr_str.find(".", idx2 + 1);

		// debug
		/*
		std::cout << idx1 << " " << idx2 << " " << idx3 << std::endl;

		std::cout << std::stoi(addr_str.substr(0, idx1)) << std::endl;
		std::cout << std::stoi(addr_str.substr(idx1 + 1, idx2)) << std::endl;
		std::cout << std::stoi(addr_str.substr(idx2 + 1, idx3)) << std::endl;
		std::cout << std::stoi(addr_str.substr(idx3 + 1, addr_str.length() - 1)) << std::endl;
		*/

		address_struct addr;
		addr.a = std::stoi(addr_str.substr(0, idx1));
		addr.b = std::stoi(addr_str.substr(idx1 + 1, idx2));
		addr.c = std::stoi(addr_str.substr(idx2 + 1, idx3));
		addr.d = std::stoi(addr_str.substr(idx3 + 1, addr_str.length() - 1));
		return addr;
	}

	address_struct::address_struct()
	{
		a = b = c = d = -1;
	}

	bool address_struct::operator==(address_struct lhs)
	{
		return a != -1
			&& a == lhs.a
			&& b == lhs.b
			&& c == lhs.c
			&& d == lhs.d;
	}
}

