#ifndef GUARD_cli_h
#define GUARD_cli_h

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <map>
#include "../engine/engine.h"

class CliParser {
public:
    const static int RC_CONTINUE=0;
    const static int RC_BREAK=1;
    const static int RC_BAD_CMD=10;
    CliParser(Engine& e): prompt("$") { engine = &e; }
//    ~CliParser() { delete(engine); }

    int run(std::istream&, std::ostream&);
    int handle_command(std::map<std::string, std::string>);
private:
    Engine *engine;
    void log_command(std::ostream&, std::map<std::string, std::string>);
    void set_prompt(std::string);
    std::string prompt;

}; 
#endif
