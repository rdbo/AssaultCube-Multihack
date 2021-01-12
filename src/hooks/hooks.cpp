#include <pch.h>
#include <base.h>

void Base::Hooks::Init()
{
	Data::oSwapBuffers = (SwapBuffers_t)mem::in::detour_trampoline(Data::pSwapBuffers, (mem::voidptr_t)Hooks::SwapBuffers, Data::szSwapBuffers, mem::MEM_DT_M1);
	Data::oShowCursor = (ShowCursor_t)mem::in::detour_trampoline(Data::pShowCursor, (mem::voidptr_t)Hooks::ShowCursor, Data::szShowCursor, mem::MEM_DT_M1);
	Data::o_c2sinfo = (c2sinfo_t)mem::in::detour_trampoline(Data::p_c2sinfo, (mem::voidptr_t)Hooks::c2sinfo, Data::sz_c2sinfo, mem::MEM_DT_M1);
}

void Base::Hooks::Shutdown()
{
	SetWindowLongPtr(Data::hWindow, GWL_WNDPROC, (LONG_PTR)Data::oWndProc);
	mem::in::detour_restore(Data::pSwapBuffers, (mem::byte_t*)Data::oSwapBuffers, Data::szSwapBuffers);
	mem::in::detour_restore(Data::pShowCursor, (mem::byte_t*)Data::oShowCursor, Data::szShowCursor);
}