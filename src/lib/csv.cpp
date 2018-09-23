#include <string>
#include <iostream>
#include <fstream>
#include "csv.h"

using std::string;
using std::ifstream;

string CsvFile::print(int line, int count){
    ifstream file(name.c_str());
    string output;
    string s;
    for (size_t i = 0; file && i < line+count; ++i){
        getline(file, s);
        if (i >= line) {
            output += s;
        }
    }
    return output;
}
