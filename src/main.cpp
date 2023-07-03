#include "flags.hpp"

int main (int argc, char** argv)
{
    ProgramFlags p_state;
    handle_flags (argc, argv, p_state);
    if (!(p_state.get_error_state()))
    {

    }

    return 0;
}