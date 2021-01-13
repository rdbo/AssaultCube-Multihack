#include <pch.h>
#include <base.h>

/*
//This function is causing crashes
void Base::Hooks::drawcrosshair(playerent* p, int n, struct color* c, float size)
{
	if(!Data::Settings::EnableCrosshair)
		return Data::o_drawcrosshair(p, n, c, size);
}
*/

__declspec(naked) void Base::Hooks::drawcrosshair(void)
{
	__asm
	{
		test Data::Settings::EnableCrosshair, 0x1
		jne ignore_draw

		orig_code:
		mov edi, Data::o_drawcrosshair
		jmp edi

		ignore_draw:
		ret
	}
}