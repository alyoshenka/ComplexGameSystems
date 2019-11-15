#include <iostream>
#include <WinSock2.h>
#include <stdio.h>

#pragma warning(disable:4996)

#include "Client.h"

int main()
{
	client player;
	player.initialize_client();

	// while (player.run_connection(true, true) == 0) { }
	player.part2();

	return 0;
}