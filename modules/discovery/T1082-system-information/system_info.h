#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H
#include <windows.h>

typedef struct {
    WCHAR hostname[256];
    WCHAR os_build[64];
    WCHAR product_name[128];
    WCHAR product_version[32];
    WCHAR architecture[32];
    DWORD processor_count;
} SYSTEM_INFO_RESULT;


BOOL get_os_build(
    WCHAR *build,
    WCHAR *name,
    WCHAR *version,
    DWORD bufferSize
);

BOOL collect_system_information(
    SYSTEM_INFO_RESULT *result
);

#endif