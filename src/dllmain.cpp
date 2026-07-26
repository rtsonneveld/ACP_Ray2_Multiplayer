#include "mod.h"
#include "network/network.h"
#include "display/displaymanager.h"
#include <shellapi.h>
#include <string>
#include "util/strutil.h"

#include <ACP_Ray2.h>

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

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	std::vector<std::string> args;
	std::string testMode = "";

	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			// Read from the command line if we should run test mode
			args = ReadCommandLineArguments();

			for (int i = 0;i < args.size();i++) {
				std::string arg = args[i];
				if (arg.starts_with("-testmode:")) {
					testMode = Split(arg, ':')[1];
					break;
				}
			}

			R2MP::PatchMutex();
			FHK_M_lCreateHook(&GAM_fn_vEngine, R2MP::EngineTick);
			FHK_M_lCreateHook(&GAM_fn_vDisplayAll, R2MP::DisplayAll);
			FHK_M_lCreateHook(&GLI_vComputeTextures, R2MP::ComputeTextures);
			R2MP::NET::Initialize(testMode == "server" ? R2MP::NET::EnumTestMode::SERVER : testMode == "client" ? R2MP::NET::EnumTestMode::CLIENT : R2MP::NET::EnumTestMode::NONE);
			R2MP::RegisterCommands();
			R2MP::LOG::Print("Finished starting ACP_Ray2Multiplayer");
			break;

		case DLL_PROCESS_DETACH:
			FHK_M_lDestroyHook(&GAM_fn_vEngine, R2MP::EngineTick);
			FHK_M_lDestroyHook(&GAM_fn_vDisplayAll, R2MP::DisplayAll);
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
