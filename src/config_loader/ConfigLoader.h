#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class ConfigLoader {
private:
    map<string, string> config;

    static string trim_white_space(const string &str) {
        const size_t first = str.find_first_not_of(" \t");
        if (first == string::npos) return "";
        const size_t last = str.find_last_not_of(" \t");
        return str.substr(first, (last - first + 1));
    }
};


#endif //CONFIGLOADER_H
