#include <pch.h>
#include <base.h>

void Base::Hacks::Teleport()
{
	vec* PlayerPos = (vec*)&Data::game.player1->newpos;
	if (Data::Settings::TeleportSaveQueued)
	{
		Data::Settings::TeleportPosition[0] = PlayerPos->x;
		Data::Settings::TeleportPosition[1] = PlayerPos->y;
		Data::Settings::TeleportPosition[2] = PlayerPos->z;
		Data::Settings::TeleportSaveQueued = false;
	}

	if (Data::Settings::TeleportQueued)
	{
		PlayerPos->x = Data::Settings::TeleportPosition[0];
		PlayerPos->y = Data::Settings::TeleportPosition[1];
		PlayerPos->z = Data::Settings::TeleportPosition[2];
		Data::Settings::TeleportQueued = false;
	}

	if(Data::Settings::TeleportForce[0])
		PlayerPos->x = Data::Settings::TeleportPosition[0];

	if (Data::Settings::TeleportForce[1])
		PlayerPos->y = Data::Settings::TeleportPosition[1];

	if (Data::Settings::TeleportForce[2])
		PlayerPos->z = Data::Settings::TeleportPosition[2];
}