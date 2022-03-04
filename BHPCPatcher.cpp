
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

class Patch {
    public:
        Patch(std::FILE *filePointer, std::string patchName) {
            fp = filePointer;
            name = patchName;
            state = false;
        }

        std::string getName() {
            return name;
        }

        bool getState() {
            return state;
        }

        void setState(bool state) {
          this->state = state;
        }

        virtual void apply() = 0;

    protected:
        std::FILE *fp;
        std::string name;
        bool state;
};

class RemoveBloom : public Patch {
    public:
        RemoveBloom(std::FILE *filePointer, std::string patchName) : Patch(filePointer, patchName) {}
        void apply() {
            /* Creator: ermaccer */
            std::fseek(fp, 0x0013D3B7, SEEK_SET); // 0x0053D3B7
            std::vector<unsigned char> patchBytes {
                0x90, // nop
                0x90, // nop
                0x90, // nop
                0x90, // nop
                0x90  // nop
            };
            std::fwrite(&patchBytes[0], sizeof(std::vector<unsigned char>::value_type), patchBytes.size(), fp);
        }
};

class EnableDbugCharacter : public Patch {
    public:
        EnableDbugCharacter(std::FILE *filePointer, std::string patchName) : Patch(filePointer, patchName) {}
        void apply() {
            /* Creator: Hexadecimal Mantis */
            std::fseek(fp, 0x00086BED, SEEK_SET); // 0x00486BED
            std::vector<unsigned char> patchBytes {
                0x74, 0x0A,                         // jz      short loc_486BF9
                0x90,                               // nop
                0x89, 0x35, 0x80, 0xE4, 0x64, 0x00, // mov     dword_64E480, esi
                0x90,                               // nop
                0x90,                               // nop
                0x90                                // nop
            };
            std::fwrite(&patchBytes[0], sizeof(std::vector<unsigned char>::value_type), patchBytes.size(), fp);
        }
};

void usage() {
    std::cout << "Usage: BHPCPatcher -e executable [-p [patch] ...]" << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "    -e, --executable    Executable to patch" << std::endl;
    std::cout << "    -p, --patch         Patch(es) to apply" << std::endl;
}

bool linearScan(std::vector<Patch *> &patchList, std::string argument) {
    bool searchFlag = false;
    for (int i = 0; i < patchList.size(); i++) {
        if (argument == patchList[i]->getName()) {
            patchList[i]->setState(true);
            searchFlag = true;
            break;
        }
    }
    return searchFlag;
}

void applyPatches(std::vector<Patch *> &patchList, bool applyAll) {
    for (int i = 0; i < patchList.size(); i++) {
        if (applyAll == true) {
            patchList[i]->setState(true);
        }
        if (patchList[i]->getState() == true) {
            std::cout << "Applying " << patchList[i]->getName() << "..." << std::endl;
            patchList[i]->apply();
        }
    }
}

void freePatches(std::vector<Patch *> &patchList) {
    for (int i = 0; i < patchList.size(); i++) {
        delete patchList[i];
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        usage();
        return 0;
    }

    if ((std::string(argv[1]) == "-e" || std::string(argv[1]) == "--executable") && (argc > 2)) {
        std::FILE *f0 = std::fopen(argv[2], "r+b");
        if (f0 == NULL) {
            std::cout << "Could not open exe!" << std::endl;
            return 1;
        }

        std::vector<Patch *> patches {
            new RemoveBloom(f0, "RemoveBloom"),
            new EnableDbugCharacter(f0, "EnableDbugCharacter")
        };

        if (argc > 3) {
            if ((std::string(argv[3]) == "-p" || std::string(argv[3]) == "--patch") && (argc > 4)) {
                for (int i = 4; i < argc; i++) {
                    if (linearScan(patches, std::string(argv[i])) == false) {
                        std::cout << "Invalid patch!" << std::endl;
                        std::fclose(f0);
                        freePatches(patches);
                        return 1;
                    }
                }
                applyPatches(patches, false);
            }
            else {
                usage();
            }
        }
        else {
            applyPatches(patches, true);
        }
        std::fclose(f0);
        freePatches(patches);
    }
    else {
        usage();
    }
    return 0;
}