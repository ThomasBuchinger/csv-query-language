#ifndef GUARD_grammar_cli_h
#define GUARD_grammar_cli_h

#include <string>
#include <tao/pegtl.hpp>
#include "grammar_cmd.h"

namespace cli {
    // Forward declarations
    

    // Top-Level Rules
    struct grammar:
        tao::pegtl::sor<
            open_cmd,
            command
        >
    {};

}

#endif
