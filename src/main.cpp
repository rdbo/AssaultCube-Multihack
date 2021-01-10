#include <pch.h>
#include <base.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	case DLL_PROCESS_ATTACH: Base::Init(hModule); break;
	case DLL_PROCESS_DETACH: Base::Shutdown(); break;
	}
	return TRUE;
}