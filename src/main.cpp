#include "flags.hpp"
#include "rom.hpp"

int main (int argc, char** argv)
{
    ProgramFlags p_flags;
    p_flags.handle_arguments (argc, argv);
    if (!(p_flags.get_error_state()))
    {
        Rom test;
        test.set_file_name ("Makefile");
        test.calculate_hashes();
        test.calculate_file_size();
        test.print_hashes();
    }

    return 0;
}