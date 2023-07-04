#include "interface.hpp"

#include <iostream>


void print_program_usage()
{
    std::cout << "\nUsage: hash [options]"
              << "\nOptions:"
              << "\n\t-s, --silent           \t\tOperate in silent mode (only prints out errors)."
              << "\n\t-r [dir], --roms=[dir] \t\tSpecify the directory ROMs are located in."
              << "\n\t-f [dir], --files=[dir]\t\tSpecify the directory hash files are located in."
              << std::endl;
}