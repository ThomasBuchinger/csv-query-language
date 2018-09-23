#ifndef GUARD_file_info_h
#define GUARD_file_info_h

#include <string>
#include "../lib/abstract_file.h"

class FileInfo {
public: 
    std::string name;
    std::string path;
    std::string type;

    FileInfo(std::string n, std::string p, std::string t): f(0) {
        name = n;
        path = p;
        type = t;
    }

private:
    AbstractFile* f;

};
#endif
