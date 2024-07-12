#include "includes.h"
#include "memory/engine.hpp"
#include "memory/loops.hpp"

using json = nlohmann::json;

int main()
{
    const wchar_t* title = L"cod ww2 zombies by suspectedesp on UnknownCheats";
    SetConsoleTitle(title);

    HWND hwnd = FindWindow(NULL, L"Call of Duty®: WWII Multiplayer");
    bool allowwithoutwindow = GetBooleanFromJSON("debug-mode", "false");
    if (hwnd == NULL)
    {
        std::cout << "Cannot find window, open Call of Duty: WWII Multiplayer" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (allowwithoutwindow) {
            std::cout << "Debug mode is activated, starting regardless" << std::endl;
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
        std::cout << "Cannot obtain process handle" << std::endl;
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