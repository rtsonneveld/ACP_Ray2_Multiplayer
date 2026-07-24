#include "mod.h"
#include <r2console_api.h>

tdfnCommand fn_vMultiplayer;

void MOD_RegisterCommands() {
	fn_vRegisterCommand("multiplayer", fn_vMultiplayer);
	fn_vRegisterCommand("mp", fn_vMultiplayer);
	LOG_Print("Registered commands!");
}

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