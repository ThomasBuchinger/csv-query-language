#ifndef GUARD_cli_h
#define GUARD_cli_h

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <map>

class CliParser {
public:
    CliParser(): prompt("$") {}

    int run();
    int handle_command(std::string);
    std::map<std::string, std::string> parse_kv(std::string);
private:
    bool command_ended(std::string);
    void set_prompt(std::string);
    std::string prompt;
}; 

bool isequalsign(char c);
#endif
