#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Info(playerinfo_t* p_info)
{
	if (!p_info || !p_info->is_valid || !((Data::Settings::EnableEspTeam && p_info->ent->team == Data::game.player1->team) || (Data::Settings::EnableEspEnemy && p_info->ent->team != Data::game.player1->team))) return;

	ImDrawList* Draw = ImGui::GetBackgroundDrawList();
	float Height = p_info->pos2D.y - p_info->headpos2D.y;
	float BarWidth = Height / 2;
	float BarHeight = Height / 20;
	float Padding = Height / 14;
	float Space = 0.0f;

	if (Data::Settings::EnableEspHealth)
	{
		Space += Padding;
		ImVec2 HealthBarPos = ImVec2(p_info->pos2D.x - BarWidth / 2, p_info->pos2D.y + Space);
		ImVec2 HealthBarEnd = ImVec2(p_info->pos2D.x + BarWidth / 2, HealthBarPos.y + BarHeight);
		ImColor DamageColor = ImColor(Data::Settings::EspHealthDmgColor[0], Data::Settings::EspHealthDmgColor[1], Data::Settings::EspHealthDmgColor[2], Data::Settings::EspHealthDmgColor[3]);
		ImColor HealthColor = ImColor(Data::Settings::EspHealthColor[0], Data::Settings::EspHealthColor[1], Data::Settings::EspHealthColor[2], Data::Settings::EspHealthColor[3]);

		ImVec2 p1 = HealthBarPos;
		ImVec2 p2 = ImVec2(p1.x, HealthBarEnd.y);
		ImVec2 p3 = HealthBarEnd;
		ImVec2 p4 = ImVec2(p3.x, p1.y);

		Draw->AddQuadFilled(p1, p2, p3, p4, DamageColor);

		p1 = p4;
		p1.x -= ((float)p_info->ent->health / 100.0f) * BarWidth;
		p2.x = p1.x;

		Draw->AddQuadFilled(p1, p2, p3, p4, HealthColor);

		Space += BarHeight;
	}

	if (Data::Settings::EnableEspArmor)
	{
		Space += Padding;
		ImVec2 ArmorBarPos = ImVec2(p_info->pos2D.x - BarWidth / 2, p_info->pos2D.y + Space);
		ImVec2 ArmorBarEnd = ImVec2(p_info->pos2D.x + BarWidth / 2, ArmorBarPos.y + BarHeight);
		ImColor DamageColor = ImColor(Data::Settings::EspArmorDmgColor[0], Data::Settings::EspArmorDmgColor[1], Data::Settings::EspArmorDmgColor[2], Data::Settings::EspArmorDmgColor[3]);
		ImColor ArmorColor = ImColor(Data::Settings::EspArmorColor[0], Data::Settings::EspArmorColor[1], Data::Settings::EspArmorColor[2], Data::Settings::EspArmorColor[3]);

		ImVec2 p1 = ArmorBarPos;
		ImVec2 p2 = ImVec2(p1.x, ArmorBarEnd.y);
		ImVec2 p3 = ArmorBarEnd;
		ImVec2 p4 = ImVec2(p3.x, p1.y);

		Draw->AddQuadFilled(p1, p2, p3, p4, DamageColor);

		p1 = p4;
		p1.x -= ((float)p_info->ent->armour / 100.0f) * BarWidth;
		p2.x = p1.x;

		Draw->AddQuadFilled(p1, p2, p3, p4, ArmorColor);

		Space += BarHeight;
	}
}