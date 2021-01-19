#include <pch.h>
#include <base.h>

static bool bOriginal[sizeof(Base::Data::game.player1->weapons)/sizeof(Base::Data::game.player1->weapons[0])];

void Base::Hacks::AutoGuns()
{
	if (Data::Settings::EnableAutoGuns)
	{
		if (!Data::game.player1->weaponsel->info.isauto)
		{
			bOriginal[Data::game.player1->weaponsel->type] = false;
			*(bool*)& Data::game.player1->weaponsel->info.isauto = true;
		}
	}

	else if (!bOriginal[Data::game.player1->weaponsel->type] && Data::game.player1->weaponsel->info.isauto)
		*(bool*)&Data::game.player1->weaponsel->info.isauto = false;
}