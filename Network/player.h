#pragma once

#include "thirdparty/raylib/raylib.h"


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

	public:
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

		player operator = (const player &lhs);
	};
}


