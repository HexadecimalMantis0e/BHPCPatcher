#ifndef PATCH_HPP
#define PATCH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Patch {
    public:
        const std::string &getName() const;
        bool getState() const;
        void setState(bool state);
        virtual void apply() = 0;

    protected:
        Patch(std::fstream &fileStream, const std::string &patchName);
        std::fstream &fs;
        const std::string name;
        bool state;
};

class RemoveBloom : public Patch {
    public:
        RemoveBloom(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

class EnableDbugCharacter : public Patch {
    public:
        EnableDbugCharacter(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

class RemoveSaveChecksum : public Patch {
    public:
        RemoveSaveChecksum(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

class RemovePakChecksum : public Patch {
    public:
        RemovePakChecksum(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

#endif
