#include "mod.h"

/** Main command for interacting with multiplayer. */
void fn_vMultiplayer(int length, char** args) {
	if (length < 1) {
		LOG_Print("Usage: mp <search|connect|username>");
		return;
	}

	std::string command = std::string(args[0]);
	if (command == "search") {
		NTW_StartSearch();
	} else if (command == "connect") {
		NTW_ConnectToPeer();
	} else if (command == "username") {
		if (length < 2) {
			LOG_Print("Usage: mp username <username>");
			return;
		}
		NTW_SetUsername(std::string(args[1]));
	}
}

namespace R2MP {
	void MOD_RegisterCommands() {
		char name[] = "mp";
		fn_vRegisterCommand(name, fn_vMultiplayer);
	}
};