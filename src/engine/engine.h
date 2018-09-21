#ifndef GUARD_cql_engine_h
#define GUARD_cql_engine_h

#include <string>
#include <vector>
#include "file_info.h"

class Engine {
public:
    void open_file(std::string, std::string, std::string);
    void list_file();
//    void print_file(std::string, int, int);
    void close_file(std::string);

private:
    std::vector<FileInfo> files;

};

//class EngineException: public std::exception;
//class BadArgumentException: public EngineException;
//class FileException: public EngineException;

#endif
