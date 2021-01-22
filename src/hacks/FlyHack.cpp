#include <pch.h>
#include <base.h>

static bool bEnabled = false;

void Base::Hacks::FlyHack()
{
	if (Data::Settings::EnableFlyHack && ((Data::Settings::FlyHackToggle && Data::Settings::FlyHackToggleState) || (!Data::Settings::FlyHackToggle && Data::WMKeys[Data::Keys::FlyHack])))
	{
		if (Data::game.player1->spectatemode != SM_FLY)
		{
			Data::game.player1->spectatemode = SM_FLY;
			bEnabled = true;
		}
	}

	else if(bEnabled)
	{
		Data::game.player1->spectatemode = SM_NONE;
		bEnabled = false;
	}
}