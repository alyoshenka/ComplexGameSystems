
#include "game.h"
#include "server.h"
#include "client.h"

int main()
{
	GameNetwork::game app;
	GameNetwork::player p1({ 50, 50 });

	GameNetwork::server host;
	GameNetwork::client player;

	app.init();
	app.add_player(&p1);

	while (!app.should_close()) 
	{
		app.tick();
		app.draw();
	}

	app.exit();

	return 0;
}
