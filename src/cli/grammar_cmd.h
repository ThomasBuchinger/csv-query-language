#ifndef GUARD_grammar_cmd_h
#define GUARD_grammar_cmd_h

#include <string>
#include <map>
#include <iostream>
#include <tao/pegtl.hpp>

namespace cli {
    // Generic Rules
    struct spaces: 
        tao::pegtl::plus< tao::pegtl::blank >
    {};
    struct name:
        tao::pegtl::plus< tao::pegtl::alpha >
    {};
    struct value:
        tao::pegtl::sor<
            tao::pegtl::seq< tao::pegtl::one< '"'  >, tao::pegtl::star< tao::pegtl::not_one< '"'  > >, tao::pegtl::one< '"'  > >,
            tao::pegtl::seq< tao::pegtl::one< '\'' >, tao::pegtl::star< tao::pegtl::not_one< '\'' > >, tao::pegtl::one< '\'' > >,
            tao::pegtl::rep_min<1, tao::pegtl::not_one< ' ' > >
        >
    {};

    // Roles: command
    struct action: 
        name
    {};
    struct kv_arg:
        tao::pegtl::seq <
            name,
            tao::pegtl::one< '=' >,
            value
        >
    {};
    struct pos_arg:
        value
    {};

    // Rule: open-command
    struct file_path: 
        value
    {};
    struct file_name: 
        value
    {};
    struct open_cmd:
        tao::pegtl::seq <
            tao::pegtl::string<'o', 'p', 'e', 'n'>,
            spaces,
            file_path,
            tao::pegtl::opt<                
                spaces,
                tao::pegtl::string<'a', 's'>,
                spaces,
                file_name
            >,
            tao::pegtl::opt< spaces >
        >
    {};

    // Top-Level Rules
    struct command:
        tao::pegtl::seq <
          action,
          spaces,
          tao::pegtl::star< spaces, kv_arg >,
//          spaces,
//          tao::pegtl::opt< tao::pegtl::list< pos_arg, spaces > >,
          tao::pegtl::eol
        >
    {};
    

    template <typename Rule> struct impl: tao::pegtl::nothing <Rule> {};
    template <> struct impl < action > {
        template < typename Input > static void apply(const Input& in, std::map<std::string, std::string>& m) {
            m["action"] = in.string();
        }
    };
    template <> struct impl < kv_arg > {
        template < typename Input > static void apply(const Input& in, std::map<std::string, std::string>& m) {
            std::string s = in.string();
            std::string::size_type eq = s.find("=");
            
            std::string value = s.substr(eq+1);
            if (value[0] == '"' || value[0] == '\'')
                value = value.substr(1, value.size()-2);
            m[s.substr(0, eq)] = value;
        }
    };
//    template <> struct impl < value > {
//        template < typename Input > static void apply(const Input& in, std::map<std::string, std::string>& m) {
//            std::cout << "value >>" << in.string() << "<<" <<std::endl;
//            m["value"]    = in.string();
//        }
//    };
    template <> struct impl < file_path > {
        template < typename Input > static void apply(const Input& in, std::map<std::string, std::string>& m) {
            std::string value = in.string();
            std::cout << "file_path >>" << value << "<<" <<std::endl;
            m["action"]    = "open";
            if (value[0] == '"' || value[0] == '\'')
                value = value.substr(1, value.size()-2);
            m["open_path"] = value;
        }
    };
    template <> struct impl < file_name > {
        template < typename Input > static void apply(const Input& in, std::map<std::string, std::string>& m) {
            std::string value = in.string();
            std::cout << "file_name >>" << value << "<<" <<std::endl;
            m["action"]    = "open";
            if (value[0] == '"' || value[0] == '\'')
                value = value.substr(1, value.size()-2);
            m["open_name"] = value;
        }
    };
}

#endif
