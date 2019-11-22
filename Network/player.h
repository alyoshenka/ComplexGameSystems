#pragma once

// #include "thirdparty/raylib/raylib.h"


namespace GameNetwork
{
	struct player
	{
		int value;

		int size;
		// Raylib::Color color;
		float speed;

		// Raylib::Vector2 pos;
		// Raylib::Vector2 dir;

	public:
		enum Direction
		{
			up,
			down,
			left,
			right
		};

		player();
		// player(Raylib::Vector2 start_pos);
		player(const player &copy_player);

		void draw();

		player operator = (const player &lhs);
	};
}


