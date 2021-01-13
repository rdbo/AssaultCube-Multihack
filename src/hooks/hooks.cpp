#include <pch.h>
#include <base.h>

void Base::Hooks::Init()
{
	Data::oSwapBuffers = (SwapBuffers_t)mem::in::detour_trampoline(Data::pSwapBuffers, (mem::voidptr_t)Hooks::SwapBuffers, Data::szSwapBuffers, mem::MEM_DT_M1);
	Data::oShowCursor = (ShowCursor_t)mem::in::detour_trampoline(Data::pShowCursor, (mem::voidptr_t)Hooks::ShowCursor, Data::szShowCursor, mem::MEM_DT_M1);
	Data::o_c2sinfo = (c2sinfo_t)mem::in::detour_trampoline(Data::p_c2sinfo, (mem::voidptr_t)Hooks::c2sinfo, Data::sz_c2sinfo, mem::MEM_DT_M1);
	//Data::o_servertoclient = (servertoclient_t)mem::in::detour_trampoline(Data::p_servertoclient, (mem::voidptr_t)Hooks::servertoclient, Data::sz_servertoclient, mem::MEM_DT_M1);
	//Data::o_movelocalplayer = (movelocalplayer_t)mem::in::detour_trampoline(Data::p_movelocalplayer, (mem::voidptr_t)Hooks::movelocalplayer, Data::sz_movelocalplayer);
	Data::o_drawcrosshair = (drawcrosshair_t)mem::in::detour_trampoline(Data::p_drawcrosshair, (mem::voidptr_t)Hooks::drawcrosshair, Data::sz_drawcrosshair, mem::MEM_DT_M1);
	Data::o_attackphysics = (attackphysics_t)mem::in::detour_trampoline(Data::p_attackphysics, (mem::voidptr_t)Hooks::attackphysics, Data::sz_attackphysics, mem::MEM_DT_M1);
}

void Base::Hooks::Shutdown()
{
	SetWindowLongPtr(Data::hWindow, GWL_WNDPROC, (LONG_PTR)Data::oWndProc);
	mem::in::detour_restore(Data::p_attackphysics, (mem::byte_t*)Data::o_attackphysics, Data::sz_attackphysics);
	mem::in::detour_restore(Data::p_drawcrosshair, (mem::byte_t*)Data::o_drawcrosshair, Data::sz_drawcrosshair);
	//mem::in::detour_restore(Data::p_movelocalplayer, (mem::byte_t*)Data::o_movelocalplayer, Data::sz_movelocalplayer);
	//mem::in::detour_restore(Data::p_servertoclient, (mem::byte_t*)Data::o_servertoclient, Data::sz_servertoclient);
	mem::in::detour_restore(Data::p_c2sinfo, (mem::byte_t*)Data::o_c2sinfo, Data::sz_c2sinfo);
	mem::in::detour_restore(Data::pSwapBuffers, (mem::byte_t*)Data::oSwapBuffers, Data::szSwapBuffers);
	mem::in::detour_restore(Data::pShowCursor, (mem::byte_t*)Data::oShowCursor, Data::szShowCursor);
}