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

		if (!LastShot && pCrosshairPlayer) LastShot = now;
		if (!pCrosshairPlayer) LastShot = 0;

		if ((pCrosshairPlayer && pCrosshairPlayer->state == CS_ALIVE && !Data::game.player1->attacking && ((Data::Settings::TriggerbotDelay && (now - LastShot >= (clock_t)(Data::Settings::TriggerbotDelayValue * 1000.0f))) || !Data::Settings::TriggerbotDelay) && (pCrosshairPlayer->team != Data::game.player1->team || !m_teammode && !m_coop)) && (!Data::Settings::TriggerbotToggle && Data::WMKeys[Data::Keys::Triggerbot] || Data::Settings::TriggerbotToggle && Data::Settings::TriggerbotToggleState))
		{
			Data::game.player1->attacking = true;
			LastShot = now;
			bEnabled = true;
		}
		else if (bEnabled)
		{
			Data::game.player1->attacking = false;
			LastShot = 0;
			bEnabled = false;
		}
	}
}