#include <pch.h>
#include <base.h>

void Base::Hacks::Speedhack()
{
	if (Data::Settings::EnableSpeedhack)
	{
		float speed_val   = Data::game.player1->maxspeed * Data::Settings::SpeedhackValue;

		if (!(Data::game.player1->k_up && Data::game.player1->k_down))
		{
			if (Data::game.player1->k_up)
				Data::game.player1->move = speed_val;
			if (Data::game.player1->k_down)
				Data::game.player1->move = -speed_val;
		}

		if (!(Data::game.player1->k_left && Data::game.player1->k_right))
		{
			if (Data::game.player1->k_left)
				Data::game.player1->strafe = speed_val;
			if (Data::game.player1->k_right)
				Data::game.player1->strafe = -speed_val;
		}
	}
}