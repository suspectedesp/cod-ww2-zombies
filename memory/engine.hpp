#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

template <typename T>
BOOL WPM(HANDLE hHand, uintptr_t Address, T val) 
{
    return WriteProcessMemory(hHand, (BYTE*)Address, &val, sizeof(val), nullptr);
}

template <typename T>
inline T RPM(HANDLE hHand, uintptr_t Address) 
{
    T ret;
    ReadProcessMemory(hHand, (BYTE*)Address, &ret, sizeof(ret), nullptr);
    return ret;
}

uintptr_t GetModuleBase(const wchar_t* modName, DWORD PID) 
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
    if (hSnap != INVALID_HANDLE_VALUE) 
    {
        MODULEENTRY32W modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32FirstW(hSnap, &modEntry)) 
        {
            do {
                if (!_wcsicmp(modEntry.szModule, modName)) 
                {
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32NextW(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return 0;
}



std::string GetExecutablePath() 
{
    char buffer[MAX_PATH];
    DWORD size = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (size == 0) 
    {
        throw std::runtime_error("Failed to get executable path");
    }
    return std::string(buffer, size);
}

std::string GetExecutableDir(const std::string& executablePath) 
{
    size_t pos = executablePath.find_last_of("\\/");
    if (pos == std::string::npos) 
    {
        return ""; // No directory part found
    }
    return executablePath.substr(0, pos);
}


#endif