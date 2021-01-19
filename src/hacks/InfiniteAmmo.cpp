#include <pch.h>
#include <base.h>

void Base::Hacks::InfiniteAmmo()
{
	if (Data::Settings::EnableServerSide && Data::Settings::EnableInfiniteAmmo)
	{
		int wpn_count = sizeof(Data::game.player1->weapons)/sizeof(Data::game.player1->weapons[0]);
		for (int i = 0; i < wpn_count; i++)
		{
			weapon* wpn = Data::game.player1->weapons[i];
			if (wpn->mag < wpn->info.magsize)
				wpn->mag = wpn->info.magsize;
			if (wpn->ammo < wpn->info.magsize)
				wpn->ammo = wpn->info.magsize;
		}
	}
}