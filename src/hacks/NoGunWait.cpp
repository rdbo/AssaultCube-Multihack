#include <pch.h>
#include <base.h>

void Base::Hacks::NoGunWait()
{
	if (Data::Settings::EnableServerSide && Data::Settings::EnableNoGunWait)
	{
		if (Data::game.player1->weaponsel->gunwait > 0)
			Data::game.player1->weaponsel->gunwait = 0;
	}
}