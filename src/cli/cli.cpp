#include <iostream>
#include <vector>
#include <exception>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include "../engine/engine.h"
#include "cli.h"

using std::endl;
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::map;

int CliParser::run(){
    string current_line;
    string command;
    vector<string> cmd_vec;
    try {
        if (!cin)
            return 2;
        while(cin) {
            cout << prompt << " ";
            getline(cin, current_line);
            if (current_line.empty())
                continue;
            int rc = handle_command(current_line);
            if (rc == 1)
              break;
        }
        return 0;
    } catch (std::exception e){
      // This will hande EngineExceptions
      cout << "Command filed:" << e.what() << endl;
      return 1;
    }
}
int CliParser::handle_command(string cmd_line) {
    static Engine engine;
    vector<string> cmd_vec;
    boost::split(cmd_vec, cmd_line, isspace);
    map<string, string> vars = parse_kv(cmd_line);
    string cmd = cmd_vec[0];
    if (cmd == "open") {
        cout << "open(): " << endl;
        engine.open_file(vars["path"], vars["name"], "csv");
        return 0;
    } else if ( cmd == "list") {
        cout << "list(): " << endl;
        engine.list_file();
        return 0;
    } else if ( cmd == "exit") {
        cout << "Bye!" << endl;
        return 1;
    } else {
        cout << "Command not found" << endl;
        return 10;
    }
}
map<string, string> CliParser::parse_kv(string cmd_line) {
    map<string, string> vm;
    vector<string> vec, h;
    string key, value;
    typedef vector<string>::size_type vec_s;
    boost::split(vec, cmd_line, isequalsign);
    for(vec_s i = 0; i != vec.size(); ++i) {
        if ( i+1 == vec.size())
            break;
        boost::split(h, vec[i], isspace);
	key = h[h.size()-1];
	boost::split(h, vec[i+1], isspace);
        value = h[0];
        cout << "found var: key=" << key << " value=" << value << endl;
        vm[key] = value;
    }
    return vm;
}
bool isequalsign(char c) {
    return c == '=';
}
void CliParser::set_prompt(string s) {
    prompt = s;
}

bool CliParser::command_ended(const string cmd){
    //if (cmd.rfind(, 0) == 0) {
    //    
    //}
    return true;
}
