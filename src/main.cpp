#include "files.hpp"
#include "flags.hpp"
#include "interface.hpp"
#include "rom.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    ProgramFlags p_flags;
    p_flags.handle_arguments (argc, argv);
    if (!(p_flags.get_exit_state()))
    {
        std::vector<Rom> rom_index;
        gen_dir_index (p_flags.get_rom_dir(), rom_index);
        for (unsigned int i = 0; i < rom_index.size(); i++)
            rom_index[i].print_hashes();
    }
    else
    {
        print_program_usage();
    }

    std::cout << std::endl;
    return 0;
}