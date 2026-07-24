#pragma once

#include <windows.h>
#include <string>

/** Copies the given text to the clipboard. */
void SetClipboard(const std::string& text) {
    if (!OpenClipboard(nullptr)) {
        return;
    }
    EmptyClipboard();
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!memory) {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(memory), text.c_str(), text.size() + 1);
    GlobalUnlock(memory);
    SetClipboardData(CF_TEXT, memory);
    CloseClipboard();
}

/** Reads the value currently in the clipboard. */
std::string ReadClipboard() {
    std::string result;
    if (!OpenClipboard(nullptr)) {
        return result;
    }
    HANDLE clipboard = GetClipboardData(CF_TEXT);
    if (clipboard != nullptr) {
        char* text = static_cast<char*>(GlobalLock(clipboard));
        if (text != nullptr) {
            result = text;
            GlobalUnlock(clipboard);
        }
    }
    CloseClipboard();
    return result;
}