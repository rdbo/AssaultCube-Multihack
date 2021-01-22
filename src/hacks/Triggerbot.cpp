#include <pch.h>
#include <base.h>

static bool bEnabled = false;
static clock_t LastShot = 0;

void Base::Hacks::Triggerbot()
{
	if (Data::Settings::EnableTriggerbot)
	{
		clock_t now = clock();

		playerent* pCrosshairPlayer = Data::game.playerincrosshair();

		if ((pCrosshairPlayer && pCrosshairPlayer->state == CS_ALIVE && !Data::game.player1->attacking && (now - LastShot >= (clock_t)(Data::Settings::TriggerbotDelay * 1000.0f)) && (pCrosshairPlayer->team != Data::game.player1->team || !m_teammode && !m_coop)) && (!Data::Settings::TriggerbotToggle && Data::WMKeys[Data::Keys::Triggerbot] || Data::Settings::TriggerbotToggle && Data::Settings::TriggerbotToggleState))
		{
			Data::game.player1->attacking = true;
			LastShot = now;
			bEnabled = true;
		}
		else if (bEnabled)
		{
			Data::game.player1->attacking = false;
			bEnabled = false;
		}
	}
}