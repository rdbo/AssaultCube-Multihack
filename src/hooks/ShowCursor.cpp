#include <pch.h>
#include <base.h>

int SDLCALL Base::Hooks::ShowCursor(int toggle)
{
	if (Data::ShowMenu)
	{
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		Data::oShowCursor(SDL_ENABLE);
	}

	else
	{
		SDL_WM_GrabInput(SDL_GRAB_ON);
		Data::oShowCursor(SDL_DISABLE);
	}

	return 0;
}