#include <pch.h>
#include <base.h>

static bool bEnabled = false;

void Base::Hacks::Triggerbot()
{
	if (Data::Settings::EnableTriggerbot)
	{
		playerent* pCrosshairPlayer = Data::game.playerincrosshair();

		if ((pCrosshairPlayer && pCrosshairPlayer->state == CS_ALIVE && (pCrosshairPlayer->team != Data::game.player1->team || !m_teammode && !m_coop)) && (!Data::Settings::TriggerbotToggle && Data::WMKeys[Data::Keys::Triggerbot] == WM_KEYDOWN || Data::Settings::TriggerbotToggle && Data::Settings::TriggerbotToggleState))
		{
			Data::game.player1->attacking = true;
			bEnabled = true;
		}
		else if (bEnabled)
		{
			Data::game.player1->attacking = false;
			bEnabled = false;
		}
	}
}