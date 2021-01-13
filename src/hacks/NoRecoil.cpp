#include <pch.h>
#include <base.h>

__declspec(naked) void Base::Hacks::NoRecoil()
{
	/*
	 * This function is symbolic
	 * The entire NoRecoil hack is
	 * handled inside the 'attackphysics' hook.
	 * This function only continues the code execution
	 */

	__asm
	{
		jmp Data::p_attackphysics_ret
	}
}