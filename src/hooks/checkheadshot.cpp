#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hooks::checkheadshot(void)
{
	__asm
	{
		jmp Hacks::AlwaysHeadshot
	}
}