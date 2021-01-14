#include <pch.h>
#include <base.h>

static bool bEnabled = false;

int SDLCALL Base::Hooks::ShowCursor(int toggle)
{
	if (Data::ShowMenu)
	{
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		Data::oShowCursor(SDL_ENABLE);
		bEnabled = true;
	}

	else if(bEnabled)
	{
		SDL_WM_GrabInput(SDL_GRAB_ON);
		Data::oShowCursor(SDL_DISABLE);
		bEnabled = false;
	}

	return 0;
}