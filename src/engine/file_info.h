#ifndef GUARD_file_info_h
#define GUARD_file_info_h

#include <string>

struct FileInfo {
    std::string name;
    std::string path;
    std::string type;

    FileInfo(std::string n, std::string p, std::string t) {
        name = n;
        path = p;
        type = t;
    }
};
#endif
