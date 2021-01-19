#include <pch.h>
#include <base.h>

HMODULE               Base::Data::hModule = NULL;
HWND                  Base::Data::hWindow = NULL;
RECT                  Base::Data::WindowRect = {};
int                   Base::Data::WindowWidth = 0;
int                   Base::Data::WindowHeight = 0;
mem::module_t         Base::Data::m_opengl;
mem::module_t         Base::Data::m_ac_client;
mem::module_t         Base::Data::m_sdl;
mem::voidptr_t        Base::Data::pSwapBuffers = nullptr;
mem::voidptr_t        Base::Data::pShowCursor = nullptr;
mem::voidptr_t        Base::Data::p_c2sinfo = nullptr;
mem::voidptr_t        Base::Data::p_servertoclient = nullptr;
mem::voidptr_t        Base::Data::p_movelocalplayer = nullptr;
mem::voidptr_t        Base::Data::p_drawcrosshair = nullptr;
mem::voidptr_t        Base::Data::p_attackphysics = nullptr;
mem::voidptr_t        Base::Data::p_attackphysics_ret = nullptr;
mem::voidptr_t        Base::Data::p_drawscope = nullptr;
mem::voidptr_t        Base::Data::p_dodamage = nullptr;
mem::voidptr_t        Base::Data::p_dodamage2 = nullptr;
mem::voidptr_t        Base::Data::p_checkheadshot = nullptr;
SwapBuffers_t         Base::Data::oSwapBuffers = nullptr;
WndProc_t             Base::Data::oWndProc = nullptr;
ShowCursor_t          Base::Data::oShowCursor = nullptr;
c2sinfo_t             Base::Data::o_c2sinfo = nullptr;
servertoclient_t      Base::Data::o_servertoclient = nullptr;
movelocalplayer_t     Base::Data::o_movelocalplayer = nullptr;
drawcrosshair_t       Base::Data::o_drawcrosshair = nullptr;
attackphysics_t       Base::Data::o_attackphysics = nullptr;
drawscope_t           Base::Data::o_drawscope = nullptr;
glDrawRangeElements_t Base::Data::o_glDrawRangeElements = nullptr;
dodamage_t            Base::Data::o_dodamage = nullptr;
dodamage2_t           Base::Data::o_dodamage2 = nullptr;
midfunction_t         Base::Data::o_checkheadshot = nullptr;
mem::size_t           Base::Data::szSwapBuffers = 5;
mem::size_t           Base::Data::szShowCursor  = 5;
mem::size_t           Base::Data::sz_c2sinfo    = 5;
mem::size_t           Base::Data::sz_servertoclient = 6;
mem::size_t           Base::Data::sz_movelocalplayer = 8;
mem::size_t           Base::Data::sz_drawcrosshair = 5;
mem::size_t           Base::Data::sz_attackphysics = 10;
mem::size_t           Base::Data::sz_drawscope = 6;
mem::size_t           Base::Data::sz_dodamage = 6;
mem::size_t           Base::Data::sz_dodamage2 = 5;
mem::size_t           Base::Data::sz_checkheadshot = 6;
bool                  Base::Data::WMKeys[0xFE];
bool                  Base::Data::InitSwapBuffers = false;
bool                  Base::Data::IsUnloaded = false;
bool                  Base::Data::ShowMenu = true;
HGLRC                 Base::Data::glContext = NULL;
HGLRC                 Base::Data::oContext = NULL;
AC_Client             Base::Data::game;
ImFont*               Base::Data::FontTitle = nullptr;
ImFont*               Base::Data::FontMenu = nullptr;
ImFont*               Base::Data::FontHack = nullptr;
bool                  Base::Data::ShowWatermark = true;
ImColor               Base::Data::WatermarkColor = ImColor(1.0f, 0.4f, 0.4f, 1.0f);

UINT    Base::Data::Keys::Bhop = VK_SPACE;
UINT    Base::Data::Keys::Triggerbot = VK_CONTROL;
UINT    Base::Data::Keys::TeleportSavePos = VK_F1;
UINT    Base::Data::Keys::Teleport = VK_F2;
UINT    Base::Data::Keys::Aimbot = VK_CAPITAL;
UINT*   Base::Data::Keys::ToChange = nullptr;

bool    Base::Data::Settings::EnableCrosshair = false;
int     Base::Data::Settings::CrosshairType = 0;
float   Base::Data::Settings::CrosshairLength = 10.0f;
float   Base::Data::Settings::CrosshairThickness = 3.0f;
float   Base::Data::Settings::CrosshairGap = 10.0f;
bool    Base::Data::Settings::CrosshairTop = true;
bool    Base::Data::Settings::CrosshairLeft = true;
bool    Base::Data::Settings::CrosshairBottom = true;
bool    Base::Data::Settings::CrosshairRight = true;
bool    Base::Data::Settings::CrosshairDot = true;
bool    Base::Data::Settings::CrosshairDotFilled = true;
float   Base::Data::Settings::CrosshairColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

bool    Base::Data::Settings::EnableEspTeam = true;
bool    Base::Data::Settings::EnableEspEnemy = true;

bool    Base::Data::Settings::EnableEspSnaplines = false;
bool    Base::Data::Settings::EspSnaplinesVisibilityCheck = true;
float   Base::Data::Settings::EspSnaplinesThickness = 2.0f;
float   Base::Data::Settings::EspSnaplinesColorTeam[4]  = { 0.0f, 0.5f, 1.0f, 1.0f };
float   Base::Data::Settings::EspSnaplinesColorEnemy[4] = { 1.0f, 0.5f, 0.0f, 1.0f };
float   Base::Data::Settings::EspSnaplinesColorTeamVisible[4]  = { 0.0f, 0.2f, 1.0f, 1.0f };
float   Base::Data::Settings::EspSnaplinesColorEnemyVisible[4] = { 1.0f, 0.2f, 0.0f, 1.0f };
int     Base::Data::Settings::EspSnaplinesPos = 0;

bool    Base::Data::Settings::EnableEspBox = false;
bool    Base::Data::Settings::EspBoxVisibilyCheck = true;
float   Base::Data::Settings::EspBoxThickness = 2.0f;
float   Base::Data::Settings::EspBoxColorTeam[4]  = { 0.0f, 1.0f, 0.5f, 1.0f };
float   Base::Data::Settings::EspBoxColorFillTeam[4] = { 0.0f, 1.0f, 0.5f, 0.5f };
float   Base::Data::Settings::EspBoxColorEnemy[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
float   Base::Data::Settings::EspBoxColorFillEnemy[4] = { 1.0f, 1.0f, 0.0f, 0.5f };
float   Base::Data::Settings::EspBoxColorTeamVisible[4] = { 0.0f, 1.0f, 0.5f, 1.0f };
float   Base::Data::Settings::EspBoxColorFillTeamVisible[4] = { 0.0f, 1.0f, 0.5f, 0.5f };
float   Base::Data::Settings::EspBoxColorEnemyVisible[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float   Base::Data::Settings::EspBoxColorFillEnemyVisible[4] = { 1.0f, 0.0f, 0.0f, 0.5f };

bool    Base::Data::Settings::EnableTeleport = false;
bool    Base::Data::Settings::TeleportQueued = false;
bool    Base::Data::Settings::TeleportSaveQueued = false;
float   Base::Data::Settings::TeleportPosition[3] = { 0.0f, 0.0f, 0.0f };
bool    Base::Data::Settings::TeleportForce[3] = { false, false, false };

bool    Base::Data::Settings::EnableNoRecoil = false;

bool    Base::Data::Settings::EnableSpeedhack = false;
float   Base::Data::Settings::SpeedhackValue = 0.5f;

bool    Base::Data::Settings::EnableTriggerbot = false;
bool    Base::Data::Settings::TriggerbotToggle = true;
bool    Base::Data::Settings::TriggerbotToggleState = false;

bool    Base::Data::Settings::EnableFlyHack = false;

bool    Base::Data::Settings::EnableNoScope = false;

bool    Base::Data::Settings::EnableTeleportPlayers = false;
float   Base::Data::Settings::TeleportPlayersDistance = 5.0f;
bool    Base::Data::Settings::TeleportPlayersTeam = false;
bool    Base::Data::Settings::TeleportPlayersEnemy = true;

bool    Base::Data::Settings::EnableEspHealth = false;
float   Base::Data::Settings::EspHealthColor[4] = { 0.0f, 0.8f, 0.0f, 1.0f };
float   Base::Data::Settings::EspHealthDmgColor[4] = { 0.8f, 0.0f, 0.0f, 1.0f };

bool    Base::Data::Settings::EnableEspArmor;
float   Base::Data::Settings::EspArmorColor[4] = { 0.0f, 0.0f, 0.8f, 1.0f };
float   Base::Data::Settings::EspArmorDmgColor[4] = { 0.05, 0.0f, 0.0f, 1.0f };

bool    Base::Data::Settings::EnableEspName = false;
float   Base::Data::Settings::EspNameColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

bool    Base::Data::Settings::EnableBunnyhop = false;
bool    Base::Data::Settings::BunnyhopToggle = false;
bool    Base::Data::Settings::BunnyhopToggleState = false;

bool    Base::Data::Settings::EnableWallhack = false;

bool    Base::Data::Settings::EnableAimbot = false;
bool    Base::Data::Settings::AimbotToggle = false;
bool    Base::Data::Settings::AimbotToggleState = false;
bool    Base::Data::Settings::AimbotSmooth = true;
float   Base::Data::Settings::AimbotSmoothValue = 2;
int     Base::Data::Settings::AimbotTargetPreference = 0;

bool    Base::Data::Settings::EnableServerSide = false;
bool    Base::Data::Settings::EnableGodmode = false;
bool    Base::Data::Settings::EnableInstantKill = false;
bool    Base::Data::Settings::EnableInfiniteAmmo = false;
bool    Base::Data::Settings::EnableNoGunWait = false;

bool    Base::Data::Settings::EnableAlwaysHeadshot = false;

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
	Data::p_attackphysics = (mem::voidptr_t)Data::game.attackphysics;
	Data::p_attackphysics_ret = (mem::voidptr_t)(&((char*)Data::p_attackphysics)[Data::sz_attackphysics]);
	Data::p_drawscope = (mem::voidptr_t)Data::game.drawscope;
	Data::p_dodamage = (mem::voidptr_t)Data::game.dodamage;
	Data::p_dodamage2 = (mem::voidptr_t)Data::game.dodamage2;
	Data::p_checkheadshot = (mem::voidptr_t)Data::game.checkheadshot;
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