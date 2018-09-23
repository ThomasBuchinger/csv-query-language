#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "engine.h"
#include "file_info.h"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;

void Engine::open_file(map<string, string> vars) {
    string name=vars["name"];
    string path=vars["path"];
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
void Engine::close_file(FileInfo file) {
    typedef vector<FileInfo>::size_type size;
    string name = file.name;
    for (size i = 0; i != files.size(); ++i) {
        if (files[i].name == name) {
           cout << "Remove File name=" << files[i].name << " path=" << files[i].path << endl;
           files.erase(files.begin()+i);
        }
    }
}
void Engine::print_file(FileInfo file, int line, int count) {

}

