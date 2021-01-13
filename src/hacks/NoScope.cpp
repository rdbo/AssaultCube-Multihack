#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hacks::NoScope()
{
	__asm
	{
		test Data::Settings::EnableNoScope,  0x1
		je orig_code
		ret

		orig_code:
		jmp Data::o_drawscope
	}
}