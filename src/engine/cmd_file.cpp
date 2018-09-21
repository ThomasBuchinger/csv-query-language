#include <string>
#include <iostream>
#include <vector>
#include "engine.h"
#include "file_info.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

void Engine::open_file(string path, string name, string type) {
    if (name.empty()){
        name = "foo";
    }
    cout << "Add File: name=" << name << " path=" << path << endl;
    files.push_back(FileInfo(name, path, "csv"));
}

void Engine::list_file() {
    typedef vector<FileInfo>::size_type size;
    for (size i = 0; i != files.size(); ++i) {
        cout << "name=" << files[i].name << " path=" << files[i].path << endl;
    }
}
void Engine::close_file(string name) {
    typedef vector<FileInfo>::size_type size;
    for (size i = 0; i != files.size(); ++i) {
        if (files[i].name == name) {
           cout << "Remove File name=" << files[i].name << " path=" << files[i].path << endl;
           files.erase(files.begin()+i);
        }
    }
}


