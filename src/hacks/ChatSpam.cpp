#include <pch.h>
#include <base.h>

static clock_t LastMessage = 0;

void Base::Hacks::ChatSpam()
{
	if (Data::Settings::EnableChatSpam)
	{
		clock_t now = clock();

		if (!LastMessage) LastMessage = now;
		if (Data::Settings::ChatSpamDelay && now - LastMessage < (clock_t)(Data::Settings::ChatSpamDelayValue * 1000.0f)) return;

		char Message[sizeof(Data::Settings::ChatSpamText) + 2];
		switch (Data::Settings::ChatSpamType)
		{
		case 0: //None
			break;
		case 1: //Team
			snprintf(Message, sizeof(Message), "%s%s", "% ", Data::Settings::ChatSpamText);
			Data::game.toserver(Message);
			LastMessage = now;
			break;
		case 2: //All
			snprintf(Message, sizeof(Message), " %s", Data::Settings::ChatSpamText);
			Data::game.toserver(Message);
			LastMessage = now;
			break;
		default:
			Data::Settings::ChatSpamType = 0;
			break;
		}
	}
}