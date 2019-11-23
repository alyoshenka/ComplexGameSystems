#pragma once

#include "player.h"
#include "helpers.h"

namespace GameNetwork
{
	class game
	{
	protected:
		player *players[MAX_PLAYER_COUNT];
		int connected_player_count;

	public:
		game();
		~game();

		void init();
		void tick();
		void draw();
		void exit();

		bool add_player(player *new_player);
		bool check_if_new_player(address_struct queried_address);
		player* find_player(address_struct player_address);
		bool should_close();
	};
}
