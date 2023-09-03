#include "directory.hpp"
#include "flags.hpp"
#include "interface.hpp"
#include "xml.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    // Handle command-line arguments
    ProgramFlags p_state (argc, argv);
    if (!p_state.get_exit_state()) // Skip if arguments weren't formatted properly
    {
        std::vector <Xml> xml_ref_data;
        std::vector <File> unverified_files, ref_data;

        gen_dir_index (p_state.get_rom_dir(), unverified_files);
        gen_dir_index (p_state.get_hash_dir(), ref_data);
        for (unsigned int i = 0; i < ref_data.size(); i++)
            xml_ref_data.push_back (Xml (ref_data[i].get_file_name()));

        if (unverified_files.size() == 0) // No files in "roms"
            print_error ("You must provide files that need to be validated!");
        else if (xml_ref_data.size() == 0) // No files in "hashes"
            print_error ("You must provide reference data for validation!");
        else
        {
            std::cout << (xml_ref_data[0].get_file_entry (6)).get_file_name();
        }
    }

    std::cout << std::endl;
    return 0;
}