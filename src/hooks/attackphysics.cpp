#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hooks::attackphysics(void)
{
	__asm
	{
		test Data::Settings::EnableNoRecoil, 0x1
		jne ignore_recoil
		orig_code:
		jmp Data::o_attackphysics

		ignore_recoil:
		jmp Hacks::NoRecoil
	}
}