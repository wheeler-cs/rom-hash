#include "interface.hpp"

#include <iostream>


/**
 * @fn print_program_usage
 * @brief Prints a message on how to use the program and its various switches.
 */
void print_program_usage()
{
    std::cout << "\nUsage: hash [options]"
              << "\nOptions:"
              << "\n\t-s, --silent           \t\tOperate in silent mode (only prints out errors)."
              << "\n\t-r [dir], --roms=[dir] \t\tSpecify the directory ROMs are located in."
              << "\n\t-f [dir], --files=[dir]\t\tSpecify the directory hash files are located in."
              << std::endl;
}

/**
 * @fn print_error
 * @brief Prints an error message and clears the output buffer.
 */
void print_error (std::string error)
{
    std::cerr << "Error: " << error << std::endl;
}
