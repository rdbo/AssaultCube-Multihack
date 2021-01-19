#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hacks::AlwaysHeadshot()
{
	__asm
	{
		cmp esi, Data::game.player1
		jne original_code
		test Data::Settings::EnableAlwaysHeadshot, 0x1
		je original_code
		mov[esp + 0x18], cl
		jmp Data::game.doheadshot

		original_code:
		jmp Data::o_checkheadshot
	}
}