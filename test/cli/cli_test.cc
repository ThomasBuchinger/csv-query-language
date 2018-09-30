#include "mock_engine.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <map>
#include <string>
#include <iostream>
#include "../../src/cli/cli.h"


using std::map;
using std::string;
using ::testing::_;
using std::stringstream;

int test_cmd(MockEngine& e, string cmd) {
    stringstream s(cmd);
    stringstream out;
    CliParser parser(e);
    return parser.run(s, out);
}
TEST(CliParser, open_as){
    MockEngine e;
    EXPECT_CALL(e, open_file(_))
        .Times(1);
    int rc = test_cmd(e, "open a as b\n");
    EXPECT_TRUE(rc == 0);
}
TEST(CliParser, open_as_with_spaces){
    MockEngine e;
    EXPECT_CALL(e, open_file(_))
        .Times(1);
    int rc = test_cmd(e, "open    a    as    b     \n");
    EXPECT_TRUE(rc == 0);
}
TEST(CliParser, open_short){
    MockEngine e;
    EXPECT_CALL(e, open_file(_))
        .Times(1);
    int rc = test_cmd(e, "open a\n");
    EXPECT_TRUE(rc == 0);
}
TEST(CliParser, open_with_values){
    MockEngine e;
    EXPECT_CALL(e, open_file(_))
        .Times(1);
    int rc = test_cmd(e, "open \"/home/foo/project/data.csv\" as data\n");
    EXPECT_TRUE(rc == 0);
}


int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
