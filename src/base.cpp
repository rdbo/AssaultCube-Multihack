#include <pch.h>
#include <base.h>

HMODULE           Base::Data::hModule = NULL;
HWND              Base::Data::hWindow = NULL;
RECT              Base::Data::WindowRect = {};
int               Base::Data::WindowWidth = 0;
int               Base::Data::WindowHeight = 0;
mem::module_t     Base::Data::m_opengl;
mem::module_t     Base::Data::m_ac_client;
mem::module_t     Base::Data::m_sdl;
mem::voidptr_t    Base::Data::pSwapBuffers = nullptr;
mem::voidptr_t    Base::Data::pShowCursor = nullptr;
mem::voidptr_t    Base::Data::p_c2sinfo = nullptr;
mem::voidptr_t    Base::Data::p_servertoclient = nullptr;
mem::voidptr_t    Base::Data::p_movelocalplayer = nullptr;
mem::voidptr_t    Base::Data::p_drawcrosshair = nullptr;
SwapBuffers_t     Base::Data::oSwapBuffers = nullptr;
WndProc_t         Base::Data::oWndProc = nullptr;
ShowCursor_t      Base::Data::oShowCursor = nullptr;
c2sinfo_t         Base::Data::o_c2sinfo = nullptr;
servertoclient_t  Base::Data::o_servertoclient = nullptr;
movelocalplayer_t Base::Data::o_movelocalplayer = nullptr;
drawcrosshair_t   Base::Data::o_drawcrosshair = nullptr;
mem::size_t       Base::Data::szSwapBuffers = 5;
mem::size_t       Base::Data::szShowCursor  = 5;
mem::size_t       Base::Data::sz_c2sinfo    = 5;
mem::size_t       Base::Data::sz_servertoclient = 6;
mem::size_t       Base::Data::sz_movelocalplayer = 8;
mem::size_t       Base::Data::sz_drawcrosshair = 5;
UINT              Base::Data::WMKeys[0xFE];
bool              Base::Data::InitSwapBuffers = false;
bool              Base::Data::IsUnloaded = false;
bool              Base::Data::ShowMenu = true;
HGLRC             Base::Data::glContext = NULL;
HGLRC             Base::Data::oContext = NULL;
AC_Client         Base::Data::game;

bool    Base::Data::Settings::EnableCrosshair = false;
int     Base::Data::Settings::CrosshairType = 0;
float   Base::Data::Settings::CrosshairLength = 10;
float   Base::Data::Settings::CrosshairThickness = 3;
float   Base::Data::Settings::CrosshairGap = 10;
bool    Base::Data::Settings::CrosshairTop = true;
bool    Base::Data::Settings::CrosshairLeft = true;
bool    Base::Data::Settings::CrosshairBottom = true;
bool    Base::Data::Settings::CrosshairRight = true;
bool    Base::Data::Settings::CrosshairDot = true;
bool    Base::Data::Settings::CrosshairDotFilled = true;
float   Base::Data::Settings::CrosshairColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

bool    Base::Data::Settings::EnableEspSnaplines = false;
float   Base::Data::Settings::EspSnaplinesThickness = 2;
float   Base::Data::Settings::EspSnaplinesColorTeam[4]  = { 0.0f, 0.5f, 1.0f, 1.0f };
float   Base::Data::Settings::EspSnaplinesColorEnemy[4] = { 1.0f, 0.5f, 0.0f, 1.0f };
int     Base::Data::Settings::EspSnaplinesPos = 0;

bool    Base::Data::Settings::TeleportQueued = false;
bool    Base::Data::Settings::TeleportSaveQueued = false;
float   Base::Data::Settings::TeleportPosition[3];
bool    Base::Data::Settings::TeleportForce[3];

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
	Data::p_servertoclient = (mem::voidptr_t)Data::game.servertoclient;
	Data::p_movelocalplayer = (mem::voidptr_t)Data::game.movelocalplayer;
	Data::p_drawcrosshair = (mem::voidptr_t)Data::game.drawcrosshair;
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