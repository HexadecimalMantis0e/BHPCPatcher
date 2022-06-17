#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Patch.hpp"

void usage(const std::vector<Patch *> &patchList);
bool linearScan(const std::vector<Patch *> &patchList, const std::string &argument);
void applyPatches(const std::vector<Patch *> &patchList, bool applyAll);

#endif
