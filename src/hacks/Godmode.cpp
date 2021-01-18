#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hacks::Godmode()
{
	__asm
	{
		mov edi, 0x0
		ret
	}
}