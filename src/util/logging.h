#pragma once

#include <string>

/** Prints the given message to the console and logs. */
void LOG_Print(const std::string message, ...);

/** Prints the given message to the console and logs. */
void LOG_Print(const char* text, ...);

/** Polls recently printed messages and writes them to the console. */
void LOG_PollConsole();