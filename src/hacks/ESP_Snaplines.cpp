#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Snaplines(playerinfo_t* p_info)
{
	if (Data::Settings::EnableEspSnaplines && p_info && p_info->is_valid && ((Data::Settings::EnableEspTeam && p_info->ent->team == Data::game.player1->team) || (Data::Settings::EnableEspEnemy && p_info->ent->team != Data::game.player1->team)))
	{
		ImVec2 LineOrigin = {};
		ImVec2 LineEnd = {};
		switch (Data::Settings::EspSnaplinesPos)
		{
		case 0:
			LineOrigin = { (float)Data::WindowWidth / 2, (float)Data::WindowHeight };
			LineEnd = ImVec2(p_info->pos2D.x, p_info->pos2D.y);
			break;
		case 1:
			LineOrigin = { (float)Data::WindowWidth / 2, 0.0f };
			LineEnd = ImVec2(p_info->headpos2D.x, p_info->headpos2D.y);
			break;
		default:
			Data::Settings::EspSnaplinesPos = 0;
			return;
			//break;
		}

		ImDrawList* Draw = ImGui::GetBackgroundDrawList();

		float LineThickness = Data::Settings::EspSnaplinesThickness;
		ImColor LineColor = ImColor(0.0f, 0.0f, 0.0f, 0.0f);

		if (p_info->ent->team == Data::game.player1->team && (m_teammode || m_coop))
		{
			if(Data::Settings::EspSnaplinesVisibilityCheck && p_info->is_visible)
				LineColor = ImColor(Data::Settings::EspSnaplinesColorTeamVisible[0], Data::Settings::EspSnaplinesColorTeamVisible[1], Data::Settings::EspSnaplinesColorTeamVisible[2], Data::Settings::EspSnaplinesColorTeamVisible[3]);
			else
				LineColor = ImColor(Data::Settings::EspSnaplinesColorTeam[0], Data::Settings::EspSnaplinesColorTeam[1], Data::Settings::EspSnaplinesColorTeam[2], Data::Settings::EspSnaplinesColorTeam[3]);
		}
		else
		{
			if(Data::Settings::EspSnaplinesVisibilityCheck && p_info->is_visible)
				LineColor = ImColor(Data::Settings::EspSnaplinesColorEnemyVisible[0], Data::Settings::EspSnaplinesColorEnemyVisible[1], Data::Settings::EspSnaplinesColorEnemyVisible[2], Data::Settings::EspSnaplinesColorEnemyVisible[3]);
			else
				LineColor = ImColor(Data::Settings::EspSnaplinesColorEnemy[0], Data::Settings::EspSnaplinesColorEnemy[1], Data::Settings::EspSnaplinesColorEnemy[2], Data::Settings::EspSnaplinesColorEnemy[3]);
		}

		Draw->AddLine(LineOrigin, LineEnd, LineColor, LineThickness);
	}
}