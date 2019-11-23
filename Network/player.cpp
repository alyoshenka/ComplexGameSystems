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

		x = 20;
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
		DrawCircle(x, pos.y, size, color);
	}

	void player::set_address(address_struct new_address)
	{
		address = new_address;
	}

	address_struct player::get_address()
	{
		return address;
	}

	std::string player::get_address_string()
	{
		return std::to_string(address.a) + "." + std::to_string(address.b)
			+ "." + std::to_string(address.c) + "." + std::to_string(address.d);
	}

	player player::operator=(const player &lhs)
	{
		return player(lhs);
	}
}

