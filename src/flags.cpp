#include "flags.hpp"


ProgramFlags::ProgramFlags()
{
    is_silent = false;
    rom_dir = "roms";
    hash_dir = "hashes";
    error_state = false;
}


void handle_flags (int argc, char** argv, ProgramFlags& p_state)
{
    std::string arg;
    for (unsigned int i = 0; i < (unsigned int)argc; i++)
    {
        arg = argv[i];
        // Argument -s: Silent mode
        if (arg == "-s")
        {
            p_state.set_silence (true);
        }
        /*
         * Argument -r: Specify ROM directory
         * Argument -h: Specify hash file directory
         */
        else if ((arg == "-r") || (arg == "-h"))
        {
            // There are still arguments after the current one
            if ((i + 1) < (unsigned int)argc)
            {
                if (arg == "-r")
                    p_state.set_rom_dir (argv[i + 1]);
                else if (arg == "-h")
                    p_state.set_hash_dir (argv[i + 1]);
                i++;
            }
            // No more arguments, which does not work for -r and -h
            else
            {
                std::cerr << "Missing argument for " + arg + "!" << std::endl;
                p_state.set_error_state (true);
                break;
            }
        }
    }
}