#include "file_info.h"
FileInfo Engine::get_file_by_name(string name) {
    typedef vector<FileInfo>::size_type size;
    for (size i = 0; i != files.size(); ++i) {
        if (files[i].name == name) {
           return files.begin()+1;
        }
    }
}
