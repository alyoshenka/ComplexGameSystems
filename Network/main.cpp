
#include "game.h"


int main()
{
	GameNetwork::game app;
	GameNetwork::player p1;

	app.init();
	app.add_player(p1);

	while (!app.should_close()) 
	{
		app.tick();
		app.draw();
	}

	app.exit();

	return 0;
}
