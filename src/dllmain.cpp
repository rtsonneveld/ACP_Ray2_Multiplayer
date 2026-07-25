#include "mod.h"
#include "network/network.h"
#include <shellapi.h>
#include <string>
#include "util/strutil.h"

std::vector<std::string> ReadCommandLineArguments()
{
	std::vector < std::string > args;
	LPWSTR rawCommandLine = GetCommandLineW();
	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(rawCommandLine, &argc);
	if (argv != NULL) {
		for (int i = 1; i < argc; ++i) { // Skip first argument (executable path)
			args.push_back(ConvertLPCWSTRToString(argv[i]));
		}
		LocalFree(argv);
	}
	return args;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	std::vector<std::string> args;
	std::string testMode = "";

	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:

			args = ReadCommandLineArguments();

			for (int i = 0;i < args.size();i++) {
				std::string arg = args[i];
				if (arg.starts_with("-testmode:")) {
					testMode = split(arg, ':')[1];
					break;
				}
			}

			R2MP::MOD_PatchMutex();
			FHK_M_lCreateHook(&GAM_fn_vEngine, R2MP::MOD_EngineTick);
			FHK_M_lCreateHook(&GAM_fn_vDisplayAll, R2MP::MOD_fn_vDisplayAll);

			NTW_Initialize(testMode == "server" ? EnumTestMode::Server : testMode == "client" ? EnumTestMode::Client : EnumTestMode::None);
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
