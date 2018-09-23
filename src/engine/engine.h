#ifndef GUARD_cql_engine_h
#define GUARD_cql_engine_h

#include <string>
#include <vector>
#include <map>
#include "file_info.h"

class Engine {
public:
    void open_file(std::map<std::string,std::string>);
    void list_file();
    void print_file(FileInfo, int, int);
    void close_file(FileInfo);

private:
    FileInfo get_file_by_name(std::string);
    std::vector<FileInfo> files;

};

//class EngineException: public std::exception;
//class BadArgumentException: public EngineException;
//class FileException: public EngineException;

#endif
