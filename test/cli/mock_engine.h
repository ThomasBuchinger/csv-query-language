#include <string>
#include <map>
#include "gmock/gmock.h"
#include "../../src/engine/engine.h"
#include "../../src/engine/file_info.h"

class MockEngine: public Engine {
public:
    MOCK_METHOD1(open_file, void(std::map<std::string, std::string>));
    MOCK_METHOD0(list_file, void());
    MOCK_METHOD1(close_file, void(FileInfo));
};

