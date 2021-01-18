#include <pch.h>
#include <base.h>

void Base::Hacks::InfiniteAmmo()
{
	if (Data::Settings::EnableServerSide && Data::Settings::EnableInfiniteAmmo)
	{
		if (Data::game.player1->weaponsel->mag < Data::game.player1->weaponsel->info.magsize)
			Data::game.player1->weaponsel->mag = Data::game.player1->weaponsel->info.magsize;
		if (Data::game.player1->weaponsel->ammo < Data::game.player1->weaponsel->info.magsize)
			Data::game.player1->weaponsel->ammo = Data::game.player1->weaponsel->info.magsize;
	}
}