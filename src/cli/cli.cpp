#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <tao/pegtl.hpp>
#include "cli.h"
#include "../engine/engine.h"
#include "grammar_cli.h"

using std::endl;
using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::vector;
using std::string;
using std::map;

int CliParser::run(istream& in, ostream& out){
    string current_line;
    map<string, string> vars;
    size_t linecount = 0;
    try {
        if (!in)
            return 2;
        while(in) {
            out << prompt << " ";
            getline(in, current_line);
            if (current_line.empty())
                continue;
            tao::pegtl::memory_input<> p_in(current_line, "STDIN");
            tao::pegtl::parse< cli::grammar, cli::impl >(p_in, vars);
            log_command(out, vars);
            int rc = handle_command(vars);
            ++linecount;
            vars.clear();
            if (rc == 1)
              break;
        }
        return 0;
    } catch (std::exception e){
      // This will hande EngineExceptions
      out << "Command failed: " << e.what() << endl;
      return 1;
    }
}
int CliParser::handle_command(map<string, string> vars) {
//    static Engine engine;
    string action = vars["action"];    
    if (action == "open") {
        engine->open_file(vars["open_path"], vars["open_name"], vars["open_type"]);
        return RC_CONTINUE;
    } else if ( action == "list") {
        cout << "list(): " << endl;
        engine->list_file();
        return RC_CONTINUE;
    } else if ( action == "exit") {
        cout << "Bye!" << endl;
        return RC_BREAK;
    } else {
        cout << "Command not found" << endl;
        return RC_BAD_CMD;
    }
}
void CliParser::log_command(ostream& out, map<string, string> vars){
    typedef map<string, string>::const_iterator iter;
    out << "DEBUG: " << vars["action"] << ": ";
    for(iter it = vars.begin(); it != vars.end(); ++it){
        out << it->first << "=" << it->second << " ";
    }
    out << endl;
}

void CliParser::set_prompt(string s) {
    prompt = s;
}
