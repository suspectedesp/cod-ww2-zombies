#include <iostream>
#include <fstream>
#include <thread>

#include "memory/engine.hpp"
#include "json/json.hpp"
#include "memory/offsets.h"
#include "memory/loops.hpp"

using json = nlohmann::json;

using namespace std;

int main()
{
    const wchar_t* title = L"cod ww2 zombies by suspectedesp on UnknownCheats";
    SetConsoleTitle(title);

    HWND hwnd = FindWindow(NULL, L"Call of Duty®: WWII Multiplayer");
    bool allowwithoutwindow = false;
    if (hwnd == NULL) 
    {
        cout << "Cannot find window, open Call of Duty: WWII Multiplayer" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (allowwithoutwindow) {
            cout << "Debug mode is activated, starting regardless";
        }
        else {
            return 1;
        }
    }

    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if (handle == NULL) 
    {
        cout << "Cannot obtain process handle" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return 1;
    }

    uintptr_t modulebase = GetModuleBase(L"s2_mp64_ship.exe", procID);

    std::thread DisplayUsernameThread(DisplayUsername, handle, modulebase);
    std::thread gameLoopThread(GameLoop, handle, modulebase);
    DisplayUsernameThread.detach();
    gameLoopThread.detach();

    while (true) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}