#include <pch.h>
#include <base.h>

void __cdecl Base::Hooks::mousemove(int idx, int idy)
{
	if (Data::ShowMenu)
		return;
	
	return Data::o_mousemove(idx, idy);
}