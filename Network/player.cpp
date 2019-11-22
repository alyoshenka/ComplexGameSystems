#include "player.h"

namespace GameNetwork
{
	 player::player() : player({ 0,0 }) { }

	player::player(Vector2 start_pos)
	{
		value = 0;

		size = 10;
		color = RED;
		speed = 10;

		pos = start_pos;
		dir = { 1, 0 };
	}

	player::player(const player& copy_player)
	{
		value = copy_player.value;

		size = copy_player.size;
		color = copy_player.color;
		speed = copy_player.speed;

		pos = copy_player.pos;
		dir = copy_player.dir;
	}

	void player::draw()
	{
		DrawCircleV(pos, size, color);
	}

	player player::operator=(const player &lhs)
	{
		return player(lhs);
	}
}

