
#include "game.h"
#include "server.h"
#include "client.h"
#include "helpers.h"

#include <thread>


#define Server false


void client_thread(GameNetwork::client c)
{
	while(true){ c.run_connection(); }
}

int main()
{
	std::cout << sizeof(GameNetwork::player) << std::endl;

	if (Server)
	{
		GameNetwork::server host;
		host.initialize_connection();

		while (true) { host.run_connection(); }
	}
	else
	{

		GameNetwork::client player;
		player.initialize_connection();


		GameNetwork::game *app = player.get_game();
		GameNetwork::player p1({ 50, 50 });

		GameNetwork::address_struct my_address(10, 15, 20, 16);
		p1.set_address(my_address);

		app->init();
		app->add_player(&p1); // not setting address

		std::thread connection_thread(client_thread, player);

		std::cout << sizeof(p1) << std::endl;

		while (!app->should_close())
		{
			app->tick();
			app->draw();

			// connection_thread.join();
			// connect data
		}

		app->exit();
	}
	

	return 0;
}

