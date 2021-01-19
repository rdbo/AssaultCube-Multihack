#include <pch.h>
#include <base.h>

void Base::Hacks::InfiniteHealth()
{
	if (Data::Settings::EnableServerSide && Data::Settings::EnableInfiniteHealth)
	{
		if (Data::game.player1->health < 100)
			Data::game.player1->health = 100;
	}
}