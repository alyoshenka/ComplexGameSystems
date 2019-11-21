#include <iostream>

#include "client.h"


int main()
{
	Network::client player;

	player.initialize_connection();

	while (true)
	{
		player.run_connection();
	}

	return 0;
}