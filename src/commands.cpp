#include "mod.h"

namespace R2MP {
	/** Main command for interacting with multiplayer. */
	void CommandMultiplayer(int length, char** args) {
		if (length < 1) {
			LOG::Print("Usage: mp <search|connect|username>");
			return;
		}

		std::string command = std::string(args[0]);
		if (command == "search") {
			NET::StartSearch();
		} else if (command == "connect") {
			NET::ConnectToPeer();
		} else if (command == "username") {
			if (length < 2) {
				LOG::Print("Usage: mp username <username>");
				return;
			}
			NET::SetUsername(std::string(args[1]));
		}
	}

	void RegisterCommands() {
		char name[] = "mp";
		fn_vRegisterCommand(name, CommandMultiplayer);
	}
};