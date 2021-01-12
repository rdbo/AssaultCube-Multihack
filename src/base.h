#pragma once
#include <pch.h>
#include "game.h"

#define MODULE_OFFSET(mod, offset) (&((char*)mod.base)[offset])

typedef BOOL(__stdcall* SwapBuffers_t)(_In_ HDC hdc);
typedef LRESULT(CALLBACK* WndProc_t) (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
typedef int(SDLCALL* ShowCursor_t)(int toggle);

namespace Base
{
	void Init(HMODULE hMod);
	void Shutdown();
	void Unload();

	namespace Data
	{
		extern HMODULE        hModule;
		extern HWND           hWindow;
		extern mem::module_t  m_opengl;
		extern mem::module_t  m_ac_client;
		extern mem::module_t  m_sdl;
		extern mem::voidptr_t pSwapBuffers;
		extern mem::voidptr_t pShowCursor;
		extern mem::voidptr_t p_c2sinfo;
		extern SwapBuffers_t  oSwapBuffers;
		extern ShowCursor_t   oShowCursor;
		extern WndProc_t      oWndProc;
		extern c2sinfo_t      o_c2sinfo;
		extern mem::size_t    szSwapBuffers;
		extern mem::size_t    szShowCursor;
		extern mem::size_t    sz_c2sinfo;
		extern UINT           WMKeys[0xFE];
		extern bool           InitSwapBuffers;
		extern bool           IsUnloaded;
		extern bool           ShowMenu;
		extern HGLRC          glContext;
		extern HGLRC          oContext;
		extern AC_Client      game;

		namespace Settings
		{

		}

		namespace Keys
		{
			const UINT Menu   = VK_INSERT;
			const UINT Unload = VK_END;
		}
	}

	namespace Hacks
	{
		
	}

	namespace Hooks
	{
		void Init();
		void Shutdown();
		BOOL __stdcall SwapBuffers(_In_ HDC hdc);
		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		int SDLCALL ShowCursor(int toggle);
		void c2sinfo(playerent* d);
	}
}