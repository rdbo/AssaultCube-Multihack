#include <pch.h>
#include <base.h>

void Base::Hacks::Bunnyhop()
{
	if (Data::Settings::EnableBunnyhop && (Data::WMKeys[Data::Keys::Bhop] == WM_KEYDOWN && !Data::Settings::BunnyhopToggle || Data::Settings::BunnyhopToggle && Data::Settings::BunnyhopToggleState) && Data::game.player1->onfloor && !Data::game.player1->jumpnext)
		Data::game.player1->jumpnext = true;
}