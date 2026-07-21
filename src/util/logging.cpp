#include "logging.h"
#include <windows.h>
#include <queue>
#include <mutex>
#include <string>

extern "C" {
	#include <r2console_api.h>
};

std::queue<std::string> logQueue;
std::mutex logMutex;

void LOG_Print(std::string text, ...) {
	va_list args;
	va_start(args, text);
	LOG_Print(text.c_str(), args);
	va_end(args);
}

void LOG_Print(const char* text, ...) {
	va_list args;
	va_start(args, text);

	// Create a duplicate of the char so we can modify it
	char* copy = (char*) malloc(strlen(text) + 1);
	strcpy(copy, text);

	// Remove any carriage returns from the input as they crash the game
	int length = strlen(copy);
	int nullIndex = length;
	for (int i = length - 1; i >= 0; i--) {
		if (copy[i] == '\r') {
			// Move the null terminator forward to remove trailing \r's
			if (i == nullIndex - 1) {
				copy[i] = 0;
				nullIndex--;
			} else {
				copy[i] = ' ';
			}
		}
	}

	long lSize = vsnprintf(NULL, 0, copy, args);
	char* szBuffer = (char*) _alloca(lSize + 1);

	if (szBuffer) {
		vsprintf(szBuffer, copy, args);
		free(copy);

		// Append the string to the queue to put in the console next engine tick
		std::lock_guard<std::mutex> lock(logMutex);
		logQueue.push(std::string(szBuffer));

		// Print all messages to a log file
		FILE* pFile = fopen("mp_log.txt", "a");
		if (pFile != NULL) {
			fprintf(pFile, szBuffer);
			fprintf(pFile, "\n");
			fclose(pFile);
		}
	}
	va_end(args);
}

void LOG_PollConsole() {
	// Print all messages in the queue to the console
	std::lock_guard<std::mutex> lock(logMutex);
	while (!logQueue.empty()) {
		fn_vPrint(logQueue.front().c_str());
		logQueue.pop();
	}
}