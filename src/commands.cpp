#include "mod.h"

/** Main command for interacting with multiplayer. */
void fn_vMultiplayer(int length, char** args) {
	if (length < 1) {
		LOG_Print("Usage: mp <search|connect>");
		return;
	}

	std::string command = std::string(args[0]);
	if (command == "search") {
		NTW_StartSearch();
	} else if (command == "connect") {
		NTW_ConnectToPeer();
	}
}

void MOD_RegisterCommands() {
	char name[] = "mp";
	fn_vRegisterCommand(name, fn_vMultiplayer);
}