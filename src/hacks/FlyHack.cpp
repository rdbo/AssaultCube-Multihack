#include <pch.h>
#include <base.h>

void Base::Hacks::FlyHack()
{
	if (Data::Settings::EnableFlyHack)
		Data::game.player1->spectatemode = SM_FLY;
	else
		Data::game.player1->spectatemode = SM_NONE;
}