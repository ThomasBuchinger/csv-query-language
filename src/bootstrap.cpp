#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "cli/cli.h"
#include "engine/engine.h"

using std::string;

namespace po = boost::program_options;
namespace {
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 1;
    const size_t ERROR_IN_CLI = 10;
}

void print_help(std::ostream& out, po::options_description arg_spec) {
    using std::endl;
    out << "Help Text: " << endl 
         << endl
         << arg_spec << endl;
}
void print_examples(std::ostream& out, const char* executeable_name) {
    using std::endl;
    const char* bin = executeable_name;
    const char* pad = "    ";
    out << "Examples:"
         << endl << "Open files in interactive mode: " << endl << pad
         << bin  << "file1.csv file2.csv"
         << endl << "Run non-interactively: " << endl << pad
         << bin  << "-c 'SELECT name,age FROM persons;' persons.csv"
         << endl <<"Create new CSV: " << endl << pad
         << bin  << "--header -c 'SELECT name FROM persons;' persons.csv > names.csv"
         << endl;
}

po::variables_map parse_options(int argc, char** argv) {
    po::options_description arg_spec("Options");
    arg_spec.add_options()
        ("file,f", "Create new CSV File")
        ("verbose,v", "turn on verbose output")
        ("help,h", "Print Help message")
        ("cmd,c", po::value<string>(), "Run Statement and exit");
    po::positional_options_description parg_spec;
    parg_spec.add("file_list", 1);

    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(arg_spec).positional(parg_spec).run(), vm);
        if (vm.count("help")){
            print_help(std::cout, arg_spec);
            print_examples(std::cout, argv[0]);
        }
        po::notify(vm);
        return vm;
    } catch(boost::program_options::error& e) {
        std::cerr << e.what() << std::endl;
        print_help(std::cerr, arg_spec);
        exit(ERROR_IN_CLI);
    }
}

int main(int argc, char** argv) {
    try {
        po::variables_map vm = parse_options(argc, argv);
        Engine e;
        CliParser cli(e);
        cli.run(std::cin, std::cout);
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    return SUCCESS;
}
