#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hooks::drawscope()
{
	__asm
	{
		jmp Hacks::NoScope
	}
}