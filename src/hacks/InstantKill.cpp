#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hacks::InstantKill()
{
	__asm
	{
		mov edi, INT_MAX
		ret
	}
}