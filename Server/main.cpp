#include <iostream>
#include <WinSock2.h>
#include <stdio.h>

// http://www.codersblock.org/blog/multiplayer-fps-part-2

#pragma warning(disable:4996)

#include "Server.h"

int main()
{
	server host;
	host.initialize_server();

	// while (host.run_connection() == 0) { }
	host.part2();

	return 0;
}