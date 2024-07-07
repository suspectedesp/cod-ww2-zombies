#include <atomic>

#include "engine.hpp"
#include "offsets.h"
#include "../json/json.hpp"

using namespace std;

//being able to change bool outside because of atomic
atomic<bool> changedisplayname(true);

using json = nlohmann::json;

std::string GetUsernameFromJSON(const std::string& jsonFilePath) 
{
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open()) 
    {
        std::cerr << "Could not open the JSON file: " << jsonFilePath << std::endl;
        return "";
    }

    json jsonData;
    jsonFile >> jsonData;
    jsonFile.close();

    std::string username = jsonData.value("username", "default_username");
    return username;
}

std::string GetUsernameTypeFromJSON(const std::string& jsonFilePath) 
{
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open()) 
    {
        std::cerr << "Could not open the JSON file: " << jsonFilePath << std::endl;
        return "";
    }

    json jsonData;
    jsonFile >> jsonData;
    jsonFile.close();

    std::string usernameType = jsonData.value("username-type", "static");
    return usernameType;
}

void DisplayUsername(HANDLE handle, uintptr_t modulebase)
{
    uintptr_t user_address = RPM<uintptr_t>(handle, modulebase + selfUsernameAddress) + selfUsernameOffset;

    // getting path for json
    std::string executablePath = GetExecutablePath();
    std::string executableDir = GetExecutableDir(executablePath);
    std::string jsonFilePath = executableDir + "\\data.json";

    std::string username = GetUsernameFromJSON(jsonFilePath);
    std::string username_type = GetUsernameTypeFromJSON(jsonFilePath);

    std::string modifiedUsername;
    
    while (true)
    {
        if (username_type == "static") 
        {
            changedisplayname = false;
            while (!changedisplayname)
            {
                modifiedUsername = username;
                WPM(handle, user_address, modifiedUsername);
                username = GetUsernameFromJSON(jsonFilePath);
                username_type = GetUsernameTypeFromJSON(jsonFilePath);
                if (username_type != "static")
                {
                    changedisplayname = true;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        else if (username_type == "dynamic") {
            changedisplayname = true;
            while (changedisplayname) {
                for (size_t i = 0; i < username.size(); ++i) 
                {
                    for (int j = 1; j <= 9; ++j) 
                    {
                        modifiedUsername = "^" + std::to_string(j) + username.substr(0, i + 1);
                        WPM(handle, user_address, modifiedUsername);
                        std::this_thread::sleep_for(std::chrono::milliseconds(33));
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(35));

                for (int i = username.size() - 1; i >= 0; --i) 
                {
                    for (int j = 1; j <= 9; ++j) 
                    {
                        modifiedUsername = "^" + std::to_string(j) + username.substr(0, i + 1);
                        WPM(handle, user_address, modifiedUsername);
                        std::this_thread::sleep_for(std::chrono::milliseconds(33));
                    }
                }
                username = GetUsernameFromJSON(jsonFilePath);
                username_type = GetUsernameTypeFromJSON(jsonFilePath);
                if (username_type != "dynamic")
                {
                    changedisplayname = false;
                }
            }

            // Set back to default username after exiting loop
            modifiedUsername = username;
            WPM(handle, user_address, modifiedUsername);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        
    }
}



typedef uintptr_t addr_t;
void GameLoop(HANDLE handle, uintptr_t modulebase)
{
    uintptr_t _1911_pistole1Address = RPM<uintptr_t>(handle, (modulebase + _1911)) + _1911_pistole1;
    uintptr_t _1911_pistole2Address = RPM<uintptr_t>(handle, (modulebase + _1911)) + _1911_pistole2;
    uintptr_t lethalWeaponAddress = RPM<uintptr_t>(handle, (modulebase + lethalWeapon)) + lethalWeaponOffset;
    uintptr_t m1GarandAddress = RPM<uintptr_t>(handle, (modulebase + m1Garand)) + m1GarandOffset;
    uintptr_t m30LuftwaffeDrillingAddress = RPM<uintptr_t>(handle, (modulebase + m30LuftwaffeDrilling)) + m30luftwaffeDrillingOffset;
    uintptr_t m1928Address = RPM<uintptr_t>(handle, (modulebase + m1928)) + m1928Offset;
    uintptr_t machinePistole1Address = RPM<uintptr_t>(handle, (modulebase + machinePistole)) + machinePistole_pistole1;
    uintptr_t machinePistole2Address = RPM<uintptr_t>(handle, (modulebase + machinePistole)) + machinePistole_pistole2;
    uintptr_t playerhealthAddress = RPM<uintptr_t>(handle, (modulebase + selfHealthAddress)) + selfHealthOffset;
    uintptr_t svt40Address = RPM<uintptr_t>(handle, (modulebase + svt40)) + svt40Offset;
    uintptr_t type100Address = RPM<uintptr_t>(handle, (modulebase + type100)) + type100Offset;
    uintptr_t SPECIAL_ABILITYAddress = modulebase + SPECIAL_ABILITY;

    while (true) 
    {
        WPM<int>(handle, playerhealthAddress, 100);
        WPM<int>(handle, _1911_pistole1Address, 100);
        WPM<int>(handle, _1911_pistole2Address, 100);
        WPM<int>(handle, m1GarandAddress, 100);
        WPM<int>(handle, m30LuftwaffeDrillingAddress, 100);
        WPM<int>(handle, m1928Address, 100);
        WPM<int>(handle, machinePistole1Address, 100);
        WPM<int>(handle, machinePistole2Address, 100);
        WPM<int>(handle, svt40Address, 100);
        WPM<int>(handle, type100Address, 100);
        WPM<int>(handle, lethalWeaponAddress, 4);
        WPM<int>(handle, SPECIAL_ABILITYAddress, SPECIAL_ABILITY_MAX);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
