#include <Windows.h>
#include <TlHelp32.h>

#include "../include/Process.hpp"

Process::Process()
{
    pid = 0;
    handle = 0;
}

Process::~Process()
{
    CloseHandle(handle);
}

int Process::attach(std::wstring processName)
{
    HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (snapShot == INVALID_HANDLE_VALUE)
        return 0;

    // Loop through running processes
    if (Process32First(snapShot, &processEntry))
    {
        while (Process32Next(snapShot, &processEntry))
        {
            if (processEntry.szExeFile == processName)
            {
                pid = processEntry.th32ProcessID;

                if (pid)
                    handle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

                CloseHandle(snapShot);
                return pid;
            }
        }
    }

    CloseHandle(snapShot);
    return 0;
}

uintptr_t Process::getModule(std::wstring moduleName)
{
    HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    if (snapShot == INVALID_HANDLE_VALUE)
        return 0;

    // Loop through loaded modules in the program
    if (Module32First(snapShot, &moduleEntry))
    {
        while (Module32Next(snapShot, &moduleEntry))
        {
            if (moduleEntry.szModule == moduleName)
            {
                CloseHandle(snapShot);
                return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
        }
    }
    
    CloseHandle(snapShot);
    return 0;
}
