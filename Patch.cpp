#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Patch.hpp"

Patch::Patch(std::fstream &fileStream, const std::string &patchName) : fs(fileStream), name(patchName) {
    state = false;
}

const std::string &Patch::getName() const {
    return name;
}

bool Patch::getState() const {
    return state;
}

void Patch::setState(bool state) {
    this->state = state;
}

RemoveBloom::RemoveBloom(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void RemoveBloom::apply() {
    /* Creator: ermaccer */
    fs.seekp(0x0013D3B7, std::ios::beg); // 0x0053D3B7
    std::vector<unsigned char> patchBytes {
        0x90, // nop
        0x90, // nop
        0x90, // nop
        0x90, // nop
        0x90  // nop
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}

EnableDbugCharacter::EnableDbugCharacter(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void EnableDbugCharacter::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x00086BED, std::ios::beg); // 0x00486BED
    std::vector<unsigned char> patchBytes {
        0x74, 0x0A,                         // jz      short loc_486BF9
        0x90,                               // nop
        0x89, 0x35, 0x80, 0xE4, 0x64, 0x00, // mov     dword_64E480, esi
        0x90,                               // nop
        0x90,                               // nop
        0x90                                // nop
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}

RemoveSaveChecksum::RemoveSaveChecksum(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void RemoveSaveChecksum::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x0012591F, std::ios::beg); // 0x0052591F
    std::vector<unsigned char> patchBytes {
        0x83, 0xF9, 0x00, // cmp     ecx, 0
        0x75, 0x12        // jnz     short loc_525936
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}

RemovePakChecksum::RemovePakChecksum(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void RemovePakChecksum::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x0016B8D6, std::ios::beg); // 0x0056B8D6
    std::vector<unsigned char> patchBytes {
        0x8B, 0x5E, 0x08, // mov     ebx, [esi+8]
        0x8B, 0xD7,       // mov     edx, edi
        0x8B, 0xCE,       // mov     ecx, esi
        0x89, 0x6E, 0x0C, // mov     [esi+0Ch], ebp
        0x90,             // nop
        0x90,             // nop
        0x90,             // nop
        0x90,             // nop
        0x90,             // nop
        0x39, 0xD3        // cmp     ebx, edx
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}
