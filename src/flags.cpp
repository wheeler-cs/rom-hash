#include "flags.hpp"

// === Ctors =======================================================================================

ProgramFlags::ProgramFlags()
{
    is_silent = false;
    // Default directories
    rom_dir = "roms";
    hash_dir = "hashes";
    error_state = false;
}

ProgramFlags::ProgramFlags (std::string r_dir, std::string h_dir, bool silence)
{
    rom_dir = r_dir;
    hash_dir = h_dir;
    is_silent = silence;

    error_state = false;
}


// === Member methods ==============================================================================


void ProgramFlags::handle_arguments (int argc, char** argv)
{
    std::string arg = "";
    unsigned int u_argc = (unsigned int)argc;
    for (unsigned int i = 0; i < u_argc; i++)
    {
        arg = argv[i];
        // Argument -s: Silent mode
        if ((arg == "-s") || (arg == "--silent"))
        {
            is_silent = true;
        }
        /*
         * Argument -r: Specify ROM directory
         * Argument -h: Specify hash file directory
         */
        // TODO: Implement --roms=[dir] and --files=[dir]
        else if ((arg == "-r") || (arg == "-f"))
        {
            // There are still arguments after the current one
            if ((i + 1) < (unsigned int)argc)
            {
                if (arg == "-r")
                    rom_dir = (argv[i + 1]);
                else if (arg == "-f")
                    hash_dir = (argv[i + 1]);
                i++;
            }
            // No more arguments, which does not work for -r and -h
            else
            {
                std::cerr << "Missing argument for " + arg + "!" << std::endl;
                error_state = true;
                break;
            }
        }
        else if ((arg == "-u") || (arg == "--usage") ||
                 (arg == "-h") || (arg == "--help"))
        {
            error_state = true;
            break;
        }
    }
}
