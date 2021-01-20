#include <pch.h>
#include <base.h>

static bool bModified[sizeof(Base::Data::game.player1->weapons)/sizeof(Base::Data::game.player1->weapons[0])];

void Base::Hacks::AutoGuns()
{
	if (Data::Settings::EnableAutoGuns)
	{
		if (!Data::game.player1->weaponsel->info.isauto)
		{
			bModified[Data::game.player1->weaponsel->type] = true;
			*(bool*)&Data::game.player1->weaponsel->info.isauto = true;
		}
	}

	else if (bModified[Data::game.player1->weaponsel->type])
	{
		*(bool*)&Data::game.player1->weaponsel->info.isauto = !Data::game.player1->weaponsel->info.isauto;
		bModified[Data::game.player1->weaponsel->type] = false;
	}
}