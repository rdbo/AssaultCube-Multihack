#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Box(playerinfo_t* p_info)
{
	if (Data::Settings::EnableEspBox && p_info && p_info->is_valid && (Data::Settings::EspBoxTeam && p_info->ent->team == Data::game.player1->team || Data::Settings::EspBoxEnemy && p_info->ent->team != Data::game.player1->team))
	{
		ImDrawList* Draw = ImGui::GetBackgroundDrawList();
		float Height = p_info->headpos2D.y - p_info->pos2D.y;
		ImVec2 TopLeft = { p_info->headpos2D.x - Height / 4, p_info->headpos2D.y };
		ImVec2 BottomLeft = { TopLeft.x, p_info->pos2D.y };
		ImVec2 BottomRight = { p_info->pos2D.x + Height / 4, BottomLeft.y };
		ImVec2 TopRight = { BottomRight.x, TopLeft.y };
		ImColor BoxColor = {};
		ImColor BoxFillColor = {};
		float   BoxThickness = Data::Settings::EspBoxThickness;

		if (p_info->ent->team == Data::game.player1->team && (m_teammode || m_coop))
		{
			BoxColor  = ImColor(Data::Settings::EspBoxColorTeam[0], Data::Settings::EspBoxColorTeam[1], Data::Settings::EspBoxColorTeam[2], Data::Settings::EspBoxColorTeam[3]);
			BoxFillColor = ImColor(Data::Settings::EspBoxColorFillTeam[0], Data::Settings::EspBoxColorFillTeam[1], Data::Settings::EspBoxColorFillTeam[2], Data::Settings::EspBoxColorFillTeam[3]);
		}

		else
		{
			BoxColor  = ImColor(Data::Settings::EspBoxColorEnemy[0], Data::Settings::EspBoxColorEnemy[1], Data::Settings::EspBoxColorEnemy[2], Data::Settings::EspBoxColorEnemy[3]);
			BoxFillColor = ImColor(Data::Settings::EspBoxColorFillEnemy[0], Data::Settings::EspBoxColorFillEnemy[1], Data::Settings::EspBoxColorFillEnemy[2], Data::Settings::EspBoxColorFillEnemy[3]);
		}

		Draw->AddQuadFilled(TopLeft, BottomLeft, BottomRight, TopRight, BoxFillColor);
		Draw->AddQuad(TopLeft, BottomLeft, BottomRight, TopRight, BoxColor, BoxThickness);
	}
}