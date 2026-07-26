#include <string>
#include <wtypes.h>
#include <vector>

/** Converts the input string into a C++ string. */
std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr);

/** Splits the given string into a vector of strings on the given delimiter. */
std::vector<std::string> Split(const std::string& s, char delim);