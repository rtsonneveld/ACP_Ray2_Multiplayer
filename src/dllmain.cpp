#include "mod.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			FHK_M_lCreateHook(&GAM_fn_vEngine, MOD_EngineTick);
			NTW_test();
			break;

		case DLL_PROCESS_DETACH:
			FHK_M_lDestroyHook(&GAM_fn_vEngine, MOD_EngineTick);
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
