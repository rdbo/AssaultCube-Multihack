#include <pch.h>
#include <base.h>

void Base::Hooks::drawcrosshair(playerent* p, int n, struct color* c, float size)
{
	if(!Data::Settings::EnableCrosshair)
		return Data::o_drawcrosshair(p, n, c, size);
}