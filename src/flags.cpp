#include "flags.hpp"

#include <iostream>

// === Ctors =======================================================================================

ProgramFlags::ProgramFlags()
{
    is_silent = false;
    // Default directories
    rom_dir = "roms";
    hash_dir = "hashes";
    exit_state = false;
}

ProgramFlags::ProgramFlags (int argc, char** argv)
{
    // Set default data before attempting to load arguments (safeguard)
    is_silent = false;
    rom_dir = "roms";
    hash_dir = "hashes";
    exit_state = false;
    this->handle_arguments (argc, argv);
}

ProgramFlags::ProgramFlags (std::string r_dir, std::string h_dir, bool silence)
{
    rom_dir = r_dir;
    hash_dir = h_dir;
    is_silent = silence;

    exit_state = false;
}


// === Member methods ==============================================================================


/**
 * @fn ProgramFlags::handle_arguments
 * @brief Sets program flags based on arguments passed in upon inital execution.
 * 
 * @note If var `error_state` is set, program will exit after function execution.
 */
void ProgramFlags::handle_arguments (int argc, char** argv)
{
    std::string arg = "";
    unsigned int u_argc = (unsigned int)argc;   // Cast argc to uint once and store in var
    for (unsigned int i = 1; i < u_argc; i++)
    {
        // Get each argument and check if it has some meaningful representation
        arg = argv[i];
        // Argument -s: Silent mode
        if ((arg == "-s") || (arg == "--silent"))
        {
            is_silent = true;
        }
        /*
         * Argument -r, --roms: Specify ROM directory
         * Argument -h, --files: Specify hash file directory
         */
        else if ((arg == "-r") || (arg == "--roms") ||
                 (arg == "-f") || (arg == "--files"))
        {
            // There are still arguments after the current one
            if ((i + 1) < (unsigned int)argc)
            {
                if ((arg == "-r") || (arg == "--roms"))
                {
                    rom_dir = (argv[i + 1]);
                }
                else if ((arg == "-f") || (arg == "--files"))
                {
                    hash_dir = (argv[i + 1]);
                }
                i++;
            }
            // No more arguments in argv, which does not work for -r and -h
            else
            {
                std::cerr << "Missing argument for " + arg + "!" << std::endl;
                exit_state = true;
                break;
            }
        }
        /*
         * Argument: -u, --usage, -h, --help: Print a "usage" menu and exit program
         */
        else if ((arg == "-u") || (arg == "--usage") ||
                 (arg == "-h") || (arg == "--help"))
        {
            exit_state = true;
            break;
        }
    }
}
