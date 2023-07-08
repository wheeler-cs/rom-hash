#include "files.hpp"
#include "flags.hpp"
#include "interface.hpp"
#include "xml.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    ProgramFlags p_flags;
    p_flags.handle_arguments (argc, argv);
    if (!(p_flags.get_exit_state()))
    {
        std::vector<Rom> rom_index;
        Xml xml_data;
        /*
        gen_dir_index (p_flags.get_rom_dir(), rom_index);
        for (unsigned int i = 0; i < rom_index.size(); i++)
            xml_data.append_rom (rom_index[i]);

        xml_data.sort_data();
        for (unsigned int i = 0; i < rom_index.size(); i++)
            xml_data.print_rom (i);
        */
        xml_data.import_xml (p_flags.get_hash_dir() + "/NoIntro - GBA.dat");
        Rom test = xml_data.find_crc ("1f1c08fb");
        test.print_hashes();
    }
    else
    {
        print_program_usage();
    }

    std::cout << std::endl;
    return 0;
}