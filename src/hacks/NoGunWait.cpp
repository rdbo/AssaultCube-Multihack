#include <pch.h>
#include <base.h>

static int OriginalThrowWait = 0;

void Base::Hacks::NoGunWait()
{
	if (Data::Settings::EnableServerSide && Data::Settings::EnableNoGunWait)
	{
		if (Data::game.player1->weaponsel->gunwait > 0)
			Data::game.player1->weaponsel->gunwait = 0;

		if (Data::game.player1->weaponsel->type == GUN_GRENADE)
		{
			if (!OriginalThrowWait)
				((grenades*)Data::game.player1->weaponsel)->throwwait;

			*(int*)&((grenades*)Data::game.player1->weaponsel)->throwwait = 0;
		}
	}

	else if (OriginalThrowWait && ((grenades*)Data::game.player1->weaponsel)->throwwait != OriginalThrowWait)
	{
		*(int*)&((grenades*)Data::game.player1->weaponsel)->throwwait = OriginalThrowWait;
	}
}