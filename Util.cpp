#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Patch.hpp"
#include "Util.hpp"

void usage(const std::vector<Patch *> &patchList) {
    std::cout << "Usage: BHPCPatcher -e executable [-p [patch] ...]" << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "    -e, --executable    Executable to patch" << std::endl;
    std::cout << "    -p, --patch         Patch(es) to apply" << std::endl;
    std::cout << "Patches:" << std::endl;

    for (auto &patch : patchList) {
        std::cout << "    " << patch->getName() << std::endl;
    }
}

bool linearScan(const std::vector<Patch *> &patchList, const std::string &argument) {
    bool searchFlag = false;

    for (auto &patch : patchList) {
        if (argument == patch->getName()) {
            patch->setState(true);
            searchFlag = true;
            break;
        }
    }
    return searchFlag;
}

void applyPatches(const std::vector<Patch *> &patchList, bool applyAll) {
    for (auto &patch : patchList) {
        if (applyAll) {
            patch->setState(true);
        }

        if (patch->getState()) {
            std::cout << "Applying " << patch->getName() << "..." << std::endl;
            patch->apply();
        }
    }
}
