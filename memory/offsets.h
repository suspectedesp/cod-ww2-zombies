#pragma once
#ifndef OFFSETS_H
#define OFFSETS_H

#include <iostream>

//self
const uintptr_t selfHealthAddress = 0x0A2D7DC8;
const uintptr_t selfHealthOffset = 0x2DC;
const uintptr_t selfUsernameAddress = 0x0E4650B0;
const uintptr_t selfUsernameOffset = 0x144;

//weapons
const uintptr_t _1911 = 0x0A0C7388;
const uintptr_t _1911_pistole1 = 0x784;
const uintptr_t _1911_pistole2 = 0x780;
const uintptr_t m1Garand = 0x0A0C7388;
const uintptr_t m1GarandOffset = 0x7C8;
const uintptr_t m30LuftwaffeDrilling = 0x0A0C7388;
const uintptr_t m30luftwaffeDrillingOffset = 0x7B0;
const uintptr_t m1928 = 0x0A0C7388;
const uintptr_t m1928Offset = 0x7C8;
const uintptr_t machinePistole = 0x0A0C7388;
const uintptr_t machinePistole_pistole1 = 0x7B4;
const uintptr_t machinePistole_pistole2 = 0x7B0;
const uintptr_t type100 = 0x0A0C7388;
const uintptr_t type100Offset = 0x7C8;
const uintptr_t svt40 = 0x0A0C7388;
const uintptr_t svt40Offset = 0x7B0;

//special
#define SPECIAL_ABILITY_MAX 1073741824
const uintptr_t SPECIAL_ABILITY = 0xA4B1888;

//lethal
const uintptr_t lethalWeapon = 0x0A0C7388;
const uintptr_t lethalWeaponOffset = 0x768;

#endif