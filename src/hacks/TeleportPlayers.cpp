#include <pch.h>
#include <base.h>

void Base::Hacks::TeleportPlayers(playerent* p_ent)
{
	if (Data::Settings::EnableTeleportPlayers)
	{
		if (Data::Settings::TeleportPlayersTeam && p_ent->team == Data::game.player1->team && (m_teammode || m_coop) || Data::Settings::TeleportPlayersEnemy && p_ent->team != Data::game.player1->team)
		{
			vec pos = Data::game.player1->o;
			float yaw = Data::game.player1->yaw;
			yaw -= 90.0f;
			if (yaw < 0.0f) yaw += 360.0f;
			pos.x += cos(yaw * (PI / 180.0f)) * Data::Settings::TeleportPlayersDistance;
			pos.y += sin(yaw * (PI / 180.0f)) * Data::Settings::TeleportPlayersDistance;
			p_ent->o = pos;

			//Make teleported player look at localplayer

			float ent_yaw = Data::game.player1->yaw + 180.0f;
			if (ent_yaw > 360.0f) ent_yaw -= 360.0f;

			p_ent->yaw = ent_yaw;
			p_ent->pitch = Data::game.player1->pitch;
		}

	}
}