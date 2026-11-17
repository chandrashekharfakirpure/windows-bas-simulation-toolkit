#include <windows.h>
#include <stdio.h>
#include "system_info.h"

BOOL collect_system_information(SYSTEM_INFO_RESULT *result) {
    DWORD hostname_size = 256;
    SYSTEM_INFO native_info;

    if(!result) {
        return FALSE;
    }

    ZeroMemory(result, sizeof(*result));

    if(!GetComputerNameW(result->hostname, &hostname_size)) {
        return FALSE;
    }

    GetNativeSystemInfo(&native_info);

    result->processor_count = native_info.dwNumberOfProcessors;

    switch (native_info.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_INTEL:
            wcscpy_s(result->architecture, 32, L"x86");
            break;

        case PROCESSOR_ARCHITECTURE_AMD64:
            wcscpy_s(result->architecture, 32, L"x64");
            break;

        case PROCESSOR_ARCHITECTURE_ARM64:
            wcscpy_s(result->architecture, 32, L"ARM64");
            break;

        default:
            wcscpy_s(result->architecture, 32, L"Unknown");
            break;
    }

    return TRUE;

}

BOOL get_os_build(WCHAR *build, WCHAR *name, WCHAR *version, DWORD bufferSize)
{
    LSTATUS status;
    DWORD dataSize;
    DWORD nameSize;
    DWORD versionSize;

    if (build == NULL || bufferSize == 0) {
        return FALSE;
    }

    dataSize = bufferSize * sizeof(WCHAR);
    nameSize = bufferSize * sizeof(WCHAR);
    versionSize = bufferSize * sizeof(WCHAR);
    
    status = RegGetValueW(
        HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
        L"CurrentBuildNumber",
        RRF_RT_REG_SZ,
        NULL,
        build,
        &dataSize
    );

    RegGetValueW(
        HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
        L"ProductName",
        RRF_RT_REG_SZ,
        NULL,
        name,
        &nameSize
    );

    RegGetValueW(
        HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
        L"DisplayVersion",
        RRF_RT_REG_SZ,
        NULL,
        version,
        &versionSize
    );

    if (status != ERROR_SUCCESS) {
        wprintf(
            L"RegGetValueW failed. Error: %ld\n",
            (long)status
        );
        return FALSE;
    }

    return TRUE;
}