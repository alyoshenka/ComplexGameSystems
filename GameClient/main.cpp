#include <iostream>

#include "client.h"

#include "game.h"


int main()
{
	GameNetwork::client player;

	player.initialize_connection();

	while (true)
	{
		player.run_connection();
	}

	return 0;
}