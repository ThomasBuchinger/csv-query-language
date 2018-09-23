#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <tao/pegtl.hpp>
#include "../engine/engine.h"
#include "cli.h"
#include "grammar_cli.h"
//#include "hello_grammar.cpp"

using std::endl;
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::map;

int CliParser::run(){
    string current_line;
    map<string, string> vars;
    try {
        if (!cin)
            return 2;
        while(cin) {
            cout << prompt << " ";
            getline(cin, current_line);
            if (current_line.empty())
                continue;
            tao::pegtl::memory_input<> in(current_line, "STDIN");
            tao::pegtl::parse< cli::grammar, cli::impl >(in, vars);
            int rc = handle_command(vars);
            vars.clear();
            if (rc == 1)
              break;
        }
        return 0;
    } catch (std::exception e){
      // This will hande EngineExceptions
      cout << "Command failed: " << e.what() << endl;
      return 1;
    }
}
int CliParser::handle_command(map<string, string> vars) {
    static Engine engine;
    log_command(vars);
    string action = vars["action"];    
    if (action == "open") {
        engine.open_file(vars);
        return RC_CONTINUE;
    } else if ( action == "list") {
        cout << "list(): " << endl;
        engine.list_file();
        return RC_CONTINUE;
    } else if ( action == "exit") {
        cout << "Bye!" << endl;
        return RC_BREAK;
    } else {
        cout << "Command not found" << endl;
        return RC_BAD_CMD;
    }
}
void CliParser::log_command(map<string, string> vars){
    typedef map<string, string>::const_iterator iter;
    cout << "DEBUG: " << vars["action"] << ": ";
    for(iter it = vars.begin(); it != vars.end(); ++it){
        cout << it->first << "=" << it->second << " ";
    }
    cout << endl;
}

void CliParser::set_prompt(string s) {
    prompt = s;
}
