#include <pch.h>
#include <base.h>

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	Base::Init((HMODULE)lpReserved);
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	case DLL_PROCESS_ATTACH: CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr); break;
	case DLL_PROCESS_DETACH: Base::Shutdown(); break;
	}
	return TRUE;
}