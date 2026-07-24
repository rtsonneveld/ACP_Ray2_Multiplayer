#include "mod.h"

extern "C" {
#include <r2console_api.h>
};

/** Main command for interacting with multiplayer. */
void fn_vMultiplayer(int length, char** args) {
	if (length < 1) {
		LOG_Print("Usage: mp <search>");
		return;
	}

	char* command = args[0];
	if (_stricmp(command, "search") == 0) {
		NTW_StartSearch();
	}
}

void MOD_RegisterCommands() {
	char name[] = "mp";
	// fn_vRegisterCommand(name, fn_vMultiplayer);
	LOG_Print("Registered commands!");
}