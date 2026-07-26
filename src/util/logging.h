#pragma once

#include <windows.h>
#include <queue>
#include <mutex>
#include <string>

extern "C" {
#include <r2console_api.h>
};

namespace R2MP {
	namespace LOG {
		/** Prints the given message to the console and logs. */
		void Print(const std::string message, ...);

		/** Prints the given message to the console and logs. */
		void Print(const char* text, ...);

		/** Polls recently printed messages and writes them to the console. */
		void PollConsole();
	}
}