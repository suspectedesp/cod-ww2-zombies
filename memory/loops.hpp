#pragma once
#ifndef LOOPS_HPP
#define LOOPS_HPP

#include "../includes.h"
#include "engine.hpp"
#include "offsets.h"

using namespace std;

//being able to change bool outside because of atomic
atomic<bool> changedisplayname(true);

void DisplayUsername(HANDLE handle, uintptr_t modulebase)
{
    uintptr_t user_address = RPM<uintptr_t>(handle, modulebase + self::UsernameAddress) + self::UsernameOffset;

    std::string username = GetValueFromJSON("username", "default_username");
    std::string usernameType = GetValueFromJSON("username-type", "static");

    std::string modifiedUsername;
    
    while (true)
    {
        if (usernameType == "static")
        {
            changedisplayname = false;
            while (!changedisplayname)
            {
                modifiedUsername = username;
                WPM(handle, user_address, modifiedUsername);
                username = GetValueFromJSON("username", "default_username");
                usernameType = GetValueFromJSON("username-type", "static");
                if (usernameType != "static")
                {
                    changedisplayname = true;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        else if (usernameType == "dynamic") {
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
                username = GetValueFromJSON("username", "default_username");
                usernameType = GetValueFromJSON("username-type", "static");
                if (usernameType != "dynamic")
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

void GameLoop(HANDLE handle, uintptr_t modulebase) {
    uintptr_t _1911_pistole1Address = RPM<uintptr_t>(handle, modulebase + weapons::_1911) + weapons::_1911_pistole1;
    uintptr_t _1911_pistole2Address = RPM<uintptr_t>(handle, modulebase + weapons::_1911) + weapons::_1911_pistole2;
    uintptr_t lethalWeaponAddress = RPM<uintptr_t>(handle, modulebase + lethal::lethalWeapon) + lethal::lethalWeaponOffset;
    uintptr_t m1GarandAddress = RPM<uintptr_t>(handle, modulebase + weapons::m1Garand) + weapons::m1GarandOffset;
    uintptr_t m1928Address = RPM<uintptr_t>(handle, modulebase + weapons::m1928) + weapons::m1928Offset;
    uintptr_t m30LuftwaffeDrillingAddress = RPM<uintptr_t>(handle, modulebase + weapons::m30LuftwaffeDrilling) + weapons::m30luftwaffeDrillingOffset;
    uintptr_t machinePistole1Address = RPM<uintptr_t>(handle, modulebase + weapons::machinePistole) + weapons::machinePistole_pistole1;
    uintptr_t machinePistole2Address = RPM<uintptr_t>(handle, modulebase + weapons::machinePistole) + weapons::machinePistole_pistole2;
    uintptr_t playerhealthAddress = RPM<uintptr_t>(handle, modulebase + self::HealthAddress) + self::HealthOffset;
    uintptr_t SPECIAL_ABILITYAddress = modulebase + special::ability_address;
    uintptr_t svt40Address = RPM<uintptr_t>(handle, modulebase + weapons::svt40) + weapons::svt40Offset;
    uintptr_t type100Address = RPM<uintptr_t>(handle, modulebase + weapons::type100) + weapons::type100Offset;
    uintptr_t teslaGunAddress = RPM<uintptr_t>(handle, modulebase + weapons::teslaGun) + weapons::teslaGunOffset;

    while (true) {
        WPM<int>(handle, playerhealthAddress, 100);
        WPM<int>(handle, _1911_pistole1Address, amounts::weapons);
        WPM<int>(handle, _1911_pistole2Address, amounts::weapons);
        WPM<int>(handle, lethalWeaponAddress, amounts::lethals);
        WPM<int>(handle, m1GarandAddress, amounts::weapons);
        WPM<int>(handle, m1928Address, amounts::weapons);
        WPM<int>(handle, m30LuftwaffeDrillingAddress, amounts::weapons);
        WPM<int>(handle, machinePistole1Address, amounts::weapons);
        WPM<int>(handle, machinePistole2Address, amounts::weapons);
        WPM<int>(handle, SPECIAL_ABILITYAddress, special::ability_max_amount);
        WPM<int>(handle, svt40Address, amounts::weapons);
        WPM<int>(handle, type100Address, amounts::weapons);
        WPM<int>(handle, teslaGunAddress, amounts::weapons);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

#endif // LOOPS_HPP