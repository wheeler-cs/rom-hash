#include "flags.hpp"
#include "rom.hpp"

int main (int argc, char** argv)
{
    ProgramFlags p_flags;
    handle_flags (argc, argv, p_flags);
    if (!(p_flags.get_error_state()))
    {
        Rom test;
        test.set_file_name ("Makefile");
        test.calculate_hashes();
        test.print_hashes();
    }

    return 0;
}