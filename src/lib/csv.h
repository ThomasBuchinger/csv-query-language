#ifndef GUARD_ext_csv_h
#define GUARD_ext_csv_h

#include <string>
#include "abstract_file.h"

class CsvFile: public AbstractFile {
    std::string print(int line, int count);

private:
    char field_seperator;
    char line_seperator;
    char quote_char;
};

#endif
