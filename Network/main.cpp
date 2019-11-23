
#include "game.h"
#include "server.h"
#include "client.h"
#include "helpers.h"

#define Server false

int main()
{
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

		while (true)
		{
			player.run_connection();

			// app.tick();
			// app.draw();
		}

		// app.exit();
	}
	

	return 0;
}

