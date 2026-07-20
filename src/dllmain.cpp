#include "framework.h"
#include "network/network.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH: /* create function hooks here */
			/* FHK_fn_lCreateHook((void**)&GAM_fn_vEngine, (void*)MOD_fn_vEngine); */
			networkTest();
			break;

		case DLL_PROCESS_DETACH: /* destroy function hooks here*/
			/* FHK_fn_lDestroyHook((void**)&GAM_fn_vEngine, (void*)MOD_fn_vEngine); */
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
