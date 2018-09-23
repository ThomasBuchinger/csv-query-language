#ifndef GUARD_cli_h
#define GUARD_cli_h

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <map>

class CliParser {
public:
    const static int RC_CONTINUE=0;
    const static int RC_BREAK=1;
    const static int RC_BAD_CMD=10;
    CliParser(): prompt("$") {}

    int run();
    int handle_command(std::map<std::string, std::string>);
private:
    void log_command(std::map<std::string, std::string>);
    void set_prompt(std::string);
    std::string prompt;
}; 
#endif
