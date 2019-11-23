#include "helpers.h"
#include <cassert>

namespace GameNetwork
{
	std::string GameNetwork::socket_address_to_string(SOCKADDR_IN &addr)
	{
		int a = addr.sin_addr.S_un.S_un_b.s_b1;
		int b = addr.sin_addr.S_un.S_un_b.s_b2;
		int c = addr.sin_addr.S_un.S_un_b.s_b3;
		int d = addr.sin_addr.S_un.S_un_b.s_b4;
		std::string ret = "";
		ret += a + ".";
		ret += b + ".";
		ret += c + ".";
		ret += d;
		return ret;
	}

	address_struct char_to_address(char* addr_char)
	{
		std::string addr_str = std::string(addr_char);
		int idx1 = addr_str.find(".");
		int idx2 = addr_str.find(".", idx1 + 1);
		int idx3 = addr_str.find(".", idx2 + 1);

		std::cout << addr_char << std::endl;
		std::cout << addr_str << std::endl;
		assert(idx1 != -1);
		assert(idx2 != -1);
		assert(idx3 != -1);

		// debug
		std::cout << idx1 << " " << idx2 << " " << idx3 << std::endl;

		std::cout << std::stoi(addr_str.substr(0, idx1)) << std::endl;
		std::cout << std::stoi(addr_str.substr(idx1 + 1, idx2)) << std::endl;
		std::cout << std::stoi(addr_str.substr(idx2 + 1, idx3)) << std::endl;
		std::cout << std::stoi(addr_str.substr(idx3 + 1, addr_str.length() - 1)) << std::endl;

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

	address_struct::address_struct(int _a, int _b, int _c, int _d)
	{
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}

	bool address_struct::operator==(address_struct lhs)
	{
		return a != -1
			&& a == lhs.a
			&& b == lhs.b
			&& c == lhs.c
			&& d == lhs.d;
	}

	std::string address_struct::to_string()
	{
		std::string ret = "";
		ret += a + ".";
		ret += b + ".";
		ret += c + ".";
		ret += d;
		return ret;
	}


	bool check_address_equality(SOCKADDR_IN addr_1, SOCKADDR_IN addr_2)
	{
		return addr_1.sin_addr.S_un.S_un_b.s_b1 == addr_2.sin_addr.S_un.S_un_b.s_b1
			&& addr_1.sin_addr.S_un.S_un_b.s_b2 == addr_2.sin_addr.S_un.S_un_b.s_b2
			&& addr_1.sin_addr.S_un.S_un_b.s_b3 == addr_2.sin_addr.S_un.S_un_b.s_b3
			&& addr_1.sin_addr.S_un.S_un_b.s_b4 == addr_2.sin_addr.S_un.S_un_b.s_b4;
	}
}

