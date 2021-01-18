#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Box(playerinfo_t* p_info)
{
	if (Data::Settings::EnableEspBox && p_info && p_info->is_valid && ((Data::Settings::EnableEspTeam && p_info->ent->team == Data::game.player1->team) || (Data::Settings::EnableEspEnemy && p_info->ent->team != Data::game.player1->team)))
	{
		ImDrawList* Draw = ImGui::GetBackgroundDrawList();
		float Height = p_info->pos2D.y - p_info->headpos2D.y;
		float BoxWidth = Height / 2;
		float BoxHeight = Height;
		ImVec2 TopLeft = { p_info->pos2D.x - BoxWidth / 2, p_info->pos2D.y - BoxHeight };
		ImVec2 BottomLeft = { TopLeft.x, TopLeft.y + BoxHeight };
		ImVec2 BottomRight = { BottomLeft.x + BoxWidth, BottomLeft.y };
		ImVec2 TopRight = { BottomRight.x, TopLeft.y };
		ImColor BoxColor = {};
		ImColor BoxFillColor = {};
		float   BoxThickness = Data::Settings::EspBoxThickness;

		if (p_info->ent->team == Data::game.player1->team && (m_teammode || m_coop))
		{
			if (Data::Settings::EspBoxVisibilyCheck && p_info->is_visible)
			{
				BoxColor = ImColor(Data::Settings::EspBoxColorTeamVisible[0], Data::Settings::EspBoxColorTeamVisible[1], Data::Settings::EspBoxColorTeamVisible[2], Data::Settings::EspBoxColorTeamVisible[3]);
				BoxFillColor = ImColor(Data::Settings::EspBoxColorFillTeamVisible[0], Data::Settings::EspBoxColorFillTeamVisible[1], Data::Settings::EspBoxColorFillTeamVisible[2], Data::Settings::EspBoxColorFillTeamVisible[3]);
			}

			else
			{
				BoxColor = ImColor(Data::Settings::EspBoxColorTeam[0], Data::Settings::EspBoxColorTeam[1], Data::Settings::EspBoxColorTeam[2], Data::Settings::EspBoxColorTeam[3]);
				BoxFillColor = ImColor(Data::Settings::EspBoxColorFillTeam[0], Data::Settings::EspBoxColorFillTeam[1], Data::Settings::EspBoxColorFillTeam[2], Data::Settings::EspBoxColorFillTeam[3]);
			}
		}

		else
		{
			if (Data::Settings::EspBoxVisibilyCheck && p_info->is_visible)
			{
				BoxColor = ImColor(Data::Settings::EspBoxColorEnemyVisible[0], Data::Settings::EspBoxColorEnemyVisible[1], Data::Settings::EspBoxColorEnemyVisible[2], Data::Settings::EspBoxColorEnemyVisible[3]);
				BoxFillColor = ImColor(Data::Settings::EspBoxColorFillEnemyVisible[0], Data::Settings::EspBoxColorFillEnemyVisible[1], Data::Settings::EspBoxColorFillEnemyVisible[2], Data::Settings::EspBoxColorFillEnemyVisible[3]);
			}

			else
			{
				BoxColor = ImColor(Data::Settings::EspBoxColorEnemy[0], Data::Settings::EspBoxColorEnemy[1], Data::Settings::EspBoxColorEnemy[2], Data::Settings::EspBoxColorEnemy[3]);
				BoxFillColor = ImColor(Data::Settings::EspBoxColorFillEnemy[0], Data::Settings::EspBoxColorFillEnemy[1], Data::Settings::EspBoxColorFillEnemy[2], Data::Settings::EspBoxColorFillEnemy[3]);
			}
		}

		Draw->AddQuadFilled(TopLeft, BottomLeft, BottomRight, TopRight, BoxFillColor);
		Draw->AddQuad(TopLeft, BottomLeft, BottomRight, TopRight, BoxColor, BoxThickness);
	}
}