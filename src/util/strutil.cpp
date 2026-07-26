#include "strutil.h"
#include <sstream>
#include <codecvt>

// Source: https://www.geeksforgeeks.org/cpp/convert-lpcwstr-to-std_string-in-cpp/
std::string ConvertLPCWSTRToString(const LPCWSTR lpcwszStr) {
    // Create a converter object to convert between wide
    // strings and UTF-8 encoded strings
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > converter;

    // Create a wstring from the LPCWSTR input
    std::wstring wstr(lpcwszStr);

    // Convert the wide string to an std::string
    return converter.to_bytes(wstr);
}

// Source: https://www.cppbetterexplained.com/posts/cpp-split-string/
std::vector<std::string> Split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        parts.push_back(item);
    }
    return parts;
}