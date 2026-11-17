#include <windows.h>
#include <stdio.h>
#include "system_info.h"

int main(void) {
    SYSTEM_INFO_RESULT result;

    wprintf(L"Starting T1082 simulation...\n");

    if(!collect_system_information(&result)) {
        wprintf(L"Simulation failed. Error: %lu\n", GetLastError());
        return 1;
    }

    if (!get_os_build(result.os_build, result.product_name, result.product_version, 64)) {
        wprintf(L"Unable to retrieve OS build.\n");
        return 1;
    }

    wprintf(L"Technique: T1082\n");
    wprintf(L"Hostname: %ls\n", result.hostname);
    wprintf(L"OS build: %ls\n", result.os_build);
    wprintf(L"Product Name: %ls\n", result.product_name);
    wprintf(L"Product Version: %ls\n", result.product_version);
    wprintf(L"Architecture: %ls\n", result.architecture);
    wprintf(L"Processor Count: %lu\n", (unsigned long)result.processor_count);

    wprintf(L"T1082 simulation completed.\n");

    return 0;
}