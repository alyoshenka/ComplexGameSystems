#include "game.h"
#include "thirdparty/raylib/raylib.h"

namespace GameNetwork
{
	void game::init()
	{
		InitWindow(300, 200, "game");
	}

	void game::tick()
	{

	}

	void game::draw()
	{
		BeginDrawing();

		ClearBackground(GRAY);

		for (int i = 0; i < connected_player_count; i++)
		{
			players[i].draw();
		}

		EndDrawing();
	}

	void game::exit()
	{
		CloseWindow();
	}

	bool game::add_player(player new_player)
	{
		if (connected_player_count >= MAX_PLAYER_COUNT) { return false; }

		players[connected_player_count] = new_player;
		connected_player_count++;
		// message here

		return true;
	}

	bool game::should_close()
	{
		return WindowShouldClose();
	}
}
