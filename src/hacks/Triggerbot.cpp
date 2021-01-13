#include <pch.h>
#include <base.h>

void Base::Hacks::Triggerbot()
{
	if (Data::Settings::EnableTriggerbot)
	{
		playerent* pCrosshairPlayer = Data::game.playerincrosshair();
		if (pCrosshairPlayer && pCrosshairPlayer->team != Data::game.player1->team)
			Data::game.player1->attacking = true;
		else
			Data::game.player1->attacking = false;
	}
}