#include <pch.h>
#include <base.h>

HMODULE        Base::Data::hModule = NULL;
HWND           Base::Data::hWindow = NULL;
mem::module_t  Base::Data::m_opengl;
mem::module_t  Base::Data::m_ac_client;
mem::module_t  Base::Data::m_sdl;
mem::voidptr_t Base::Data::pSwapBuffers = nullptr;
mem::voidptr_t Base::Data::pShowCursor = nullptr;
mem::voidptr_t Base::Data::p_c2sinfo = nullptr;
SwapBuffers_t  Base::Data::oSwapBuffers = nullptr;
WndProc_t      Base::Data::oWndProc = nullptr;
ShowCursor_t   Base::Data::oShowCursor = nullptr;
c2sinfo_t      Base::Data::o_c2sinfo = nullptr;
mem::size_t    Base::Data::szSwapBuffers = 5;
mem::size_t    Base::Data::szShowCursor  = 5;
mem::size_t    Base::Data::sz_c2sinfo    = 5;
UINT           Base::Data::WMKeys[0xFE];
bool           Base::Data::InitSwapBuffers = false;
bool           Base::Data::IsUnloaded = false;
bool           Base::Data::ShowMenu = true;
HGLRC          Base::Data::glContext = NULL;
HGLRC          Base::Data::oContext = NULL;
AC_Client      Base::Data::game;

DWORD WINAPI ExitThread(LPVOID lpReserved);

void Base::Init(HMODULE hMod)
{
	Data::hModule = hMod;
	Data::m_opengl    = mem::in::get_module("OPENGL32.dll");
	Data::m_ac_client = mem::in::get_module("ac_client.exe");
	Data::m_sdl       = mem::in::get_module("SDL.dll");
	Data::game = AC_Client(&Data::m_ac_client);

	Data::pSwapBuffers = mem::in::get_symbol(Data::m_opengl, "wglSwapBuffers");
	Data::pShowCursor  = mem::in::get_symbol(Data::m_sdl, "SDL_ShowCursor");
	Data::p_c2sinfo    = (mem::voidptr_t)Data::game.c2sinfo;
	Hooks::Init();
}

void Base::Shutdown()
{
	if (!Data::IsUnloaded)
	{
		if (Data::InitSwapBuffers)
		{
			ImGui_ImplOpenGL2_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
		}

		Hooks::Shutdown();

		Data::IsUnloaded = true;
	}
}

void Base::Unload()
{
	Base::Shutdown();
	CreateThread(nullptr, 0, ExitThread, NULL, 0, nullptr);
}

DWORD WINAPI ExitThread(LPVOID lpReserved)
{
	FreeLibraryAndExitThread(Base::Data::hModule, TRUE);
	return TRUE;
}