#include <pch.h>
#include <base.h>

void Base::Hacks::InfiniteArmor()
{
	if (Data::Settings::EnableInfiniteArmor)
	{
		if (Data::game.player1->armour < 100)
			Data::game.player1->armour = 100;
	}
}