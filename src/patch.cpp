/**
 * Rayman 2 uses a mutex called `RAYMAN2EXE` to prevent multiple instances of the game
 * being open. For testing purposes we want to remove this but it's incredibly jank
 * so here's the worst code imaginably to do that.
 * 
 * We don't inject early enough to stop the game from creating the mutex so we have to
 * jankily go through the process's handle, find all mutexes created and find the one
 * we need to destroy.
 */

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string.h>

typedef LONG(NTAPI* tdfnNtQuerySystemInformation)(ULONG, PVOID, ULONG, PULONG);
typedef LONG(NTAPI* tdfnNtQueryObject)(HANDLE, ULONG, PVOID, ULONG, PULONG);

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;

typedef struct _SYSTEM_HANDLE_ENTRY_EX {
    PVOID     Object;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR HandleValue;
    ULONG     GrantedAccess;
    USHORT    CreatorBackTraceIndex;
    USHORT    ObjectTypeIndex;
    ULONG     HandleAttributes;
    ULONG     Reserved;
} SYSTEM_HANDLE_ENTRY_EX;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX {
    ULONG_PTR NumberOfHandles;
    ULONG_PTR Reserved;
    SYSTEM_HANDLE_ENTRY_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX;

namespace R2MP {
    /** Checks if the handle points to the named Mutex "RAYMAN2EXE" */
    static int IsGuardMutex(tdfnNtQueryObject pfnNtQueryObject, HANDLE hObject) {
        unsigned char aucBuf[1024];
        UNICODE_STRING* pstStr;
        ULONG ulLen;
        if (pfnNtQueryObject(hObject, 2, aucBuf, sizeof(aucBuf), &ulLen) < 0) return 0;
        pstStr = (UNICODE_STRING*) aucBuf;
        if (!pstStr->Buffer || pstStr->Length == 0) return 0;
        if (_wcsnicmp(pstStr->Buffer, L"Mutant", 6) != 0 || pstStr->Length != 6 * sizeof(WCHAR)) return 0;
        if (pfnNtQueryObject(hObject, 1, aucBuf, sizeof(aucBuf), &ulLen) < 0) return 0;
        pstStr = (UNICODE_STRING*)aucBuf;
        if (!pstStr->Buffer || pstStr->Length < sizeof(L"RAYMAN2EXE") - sizeof(WCHAR)) return 0;
        int lChars = pstStr->Length / sizeof(WCHAR);
        int lNeed = (int)(sizeof(L"RAYMAN2EXE") / sizeof(WCHAR)) - 1;
        const WCHAR* pwzTail = pstStr->Buffer + (lChars - lNeed);
        if (lChars < lNeed) return 0;
        if (_wcsnicmp(pwzTail, L"RAYMAN2EXE", lNeed) != 0) return 0;
        if (lChars > lNeed && pwzTail[-1] != L'\\') return 0;
        return 1;
    }

    void PatchMutex() {
        // Load ntdll.dll and obtain data from it
        HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
        if (!hNtdll) {
            return;
        }
        tdfnNtQuerySystemInformation pfnQSI = (tdfnNtQuerySystemInformation) GetProcAddress(hNtdll, "NtQuerySystemInformation");
        tdfnNtQueryObject pfnQO = (tdfnNtQueryObject) GetProcAddress(hNtdll, "NtQueryObject");
        if (!pfnQSI || !pfnQO) {
            return;
        }

        // Determine the current status of the process and access process memory
        DWORD ulOurPid = GetCurrentProcessId();
        ULONG ulBufSize = 0x20000;
        PVOID pBuffer = NULL;
        LONG lStatus;
        for (;;) {
            ULONG ulNeeded = 0;
            pBuffer = HeapAlloc(GetProcessHeap(), 0, ulBufSize);
            if (!pBuffer) {
                return;
            }
            lStatus = pfnQSI(64, pBuffer, ulBufSize, &ulNeeded);
            if (lStatus == ((LONG) 0xC0000004L)) {
                HeapFree(GetProcessHeap(), 0, pBuffer);
                pBuffer = NULL;
                ulBufSize = (ulNeeded > ulBufSize) ? ulNeeded + 0x10000 : ulBufSize * 2;
                if (ulBufSize > 0x4000000) return;
                continue;
            }
            break;
        }

        // If we managed to find valid status data 
        if (lStatus >= 0 && pBuffer) {
            SYSTEM_HANDLE_INFORMATION_EX* pstInfo = (SYSTEM_HANDLE_INFORMATION_EX*)pBuffer;
            for (ULONG_PTR i = 0; i < pstInfo->NumberOfHandles; i++) {
                SYSTEM_HANDLE_ENTRY_EX* pstEntry = &pstInfo->Handles[i];
                if ((DWORD)pstEntry->UniqueProcessId != ulOurPid) continue;
                HANDLE hObject = (HANDLE)pstEntry->HandleValue;
                if (IsGuardMutex(pfnQO, hObject)) {
                    CloseHandle(hObject);
                    break;
                }
            }
        }

        // Free the claimed buffer again
        if (pBuffer) {
            HeapFree(GetProcessHeap(), 0, pBuffer);
        }
    }
};