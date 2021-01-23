#include <pch.h>
#include <base.h>

void Base::Hacks::TeleportItems(entity& p_item)
{
	if (Data::Settings::EnableTeleportItems)
	{
		if (
			Data::Settings::TeleportItemsHealth  && p_item.type == I_HEALTH  ||
			Data::Settings::TeleportItemsArmor   && p_item.type == I_ARMOUR  ||
			Data::Settings::TeleportItemsArmor   && p_item.type == I_HELMET  ||
			Data::Settings::TeleportItemsGrenade && p_item.type == I_GRENADE ||
			Data::Settings::TeleportItemsAmmo    && p_item.type == I_AMMO    ||
			Data::Settings::TeleportItemsClips   && p_item.type == I_CLIPS   ||
			Data::Settings::TeleportItemsAkimbo  && p_item.type == I_AKIMBO
		)
		{
			p_item.x = Data::game.player1->o.x;
			p_item.y = Data::game.player1->o.y;
			p_item.z = Data::game.player1->o.z - Data::game.player1->eyeheight;
		}
	}
}