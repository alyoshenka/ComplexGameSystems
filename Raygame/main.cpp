#include <iostream>

#include "client.h"
#include "server.h"

int main()
{
	std::cout << "game started" << std::endl;

	server host;
	// client p1;

	host.initialize_connection();
	// p1.initialize_connection();
	
	bool game_running = true;
	while (game_running)
	{
		host.run_connection();
		// p1.run_connection();
	}

	char c;
	std::cin >> c;
	return 0;
}