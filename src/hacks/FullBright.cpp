#include <pch.h>
#include <base.h>

static bool bForced = false;

void Base::Hacks::FullBright()
{
	if (Data::Settings::EnableFullBright)
	{
		if (!(*Data::game.fullbright))
		{
			Data::game.fullbrightlight();
			bForced = true;
		}
	}

	else if (bForced)
	{
		Data::game.calclight();
		bForced = false;
	}
}