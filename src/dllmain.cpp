#include "mod.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			FHK_M_lCreateHook(&GAM_fn_vEngine, R2MP::MOD_EngineTick);
			FHK_M_lCreateHook(&GAM_fn_vDisplayAll, R2MP::MOD_fn_vDisplayAll);
			NTW_Initialize();
			R2MP::MOD_RegisterCommands();
			LOG_Print("Finished starting ACP_Ray2Multiplayer");
			break;

		case DLL_PROCESS_DETACH:
			FHK_M_lDestroyHook(&GAM_fn_vEngine, R2MP::MOD_EngineTick);
			FHK_M_lDestroyHook(&GAM_fn_vDisplayAll, R2MP::MOD_fn_vDisplayAll);
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
