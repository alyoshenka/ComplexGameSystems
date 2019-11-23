#pragma once

#include "thirdparty/raylib/raylib.h"
#include "helpers.h"


namespace GameNetwork
{
	struct player
	{
		int value;

		int size;
		Color color;
		float speed;

		Vector2 pos;
		Vector2 dir;

		address_struct address;

	public:

		int x;

		enum Direction
		{
			up,
			down,
			left,
			right
		};

		player();
		player(Vector2 start_pos);
		player(const player &copy_player);

		void draw();

		void set_address(address_struct new_address);
		address_struct get_address();
		std::string get_address_string();

		player operator = (const player &lhs);
	};
}


