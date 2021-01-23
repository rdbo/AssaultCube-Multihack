#include <pch.h>
#include <base.h>

void Base::Hacks::PingChanger()
{
	if (Data::Settings::EnablePingChanger)
	{
		Data::game.player1->ping = Data::Settings::PingChangerValue;
	}
}