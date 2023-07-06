#include "files.hpp"
#include "flags.hpp"
#include "interface.hpp"
#include "rom.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    ProgramFlags p_flags;
    p_flags.handle_arguments (argc, argv);
    if (!(p_flags.get_error_state()))
    {
        std::vector<std::string> test_v;
        gen_dir_index ("src", test_v);
        for (unsigned int i = 0; i < test_v.size(); i++)
            std::cout << test_v[i] << '\n';
    }
    else
    {
        print_program_usage();
    }

    std::cout << std::endl;
    return 0;
}