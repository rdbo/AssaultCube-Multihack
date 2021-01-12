#include <pch.h>
#include <base.h>

/* Not yet implemented */

void Base::Hacks::Teleport()
{
	if (Data::Settings::TeleportSaveQueued)
	{
		Data::Settings::TeleportPosition[0] = Data::game.player1->o.x;
		Data::Settings::TeleportPosition[1] = Data::game.player1->o.y;
		Data::Settings::TeleportPosition[2] = Data::game.player1->o.z;
		Data::Settings::TeleportSaveQueued = false;
	}

	if (Data::Settings::TeleportQueued)
	{
		Data::game.player1->o.x = Data::Settings::TeleportPosition[0];
		Data::game.player1->o.y = Data::Settings::TeleportPosition[1];
		Data::game.player1->o.z = Data::Settings::TeleportPosition[2];
		Data::Settings::TeleportQueued = false;
	}

	if(Data::Settings::TeleportForce[0])
		Data::game.player1->o.x = Data::Settings::TeleportPosition[0];

	if (Data::Settings::TeleportForce[1])
		Data::game.player1->o.x = Data::Settings::TeleportPosition[1];

	if (Data::Settings::TeleportForce[2])
		Data::game.player1->o.x = Data::Settings::TeleportPosition[2];
}