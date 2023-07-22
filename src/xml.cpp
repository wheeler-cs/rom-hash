#include "xml.hpp"

#include <fstream>
#include <iostream>


// === Ctors =======================================================================================


// === Member methods ==============================================================================


/**
 * 
 */
bool Xml::import_xml (const std::string &f_name)
{
    file_name = f_name;
    std::ifstream xml_read (file_name.c_str());
    if (xml_read.is_open())
    {
        // Read XML file into memory
        std::string file_text = "", buffer = "";
        while (std::getline (xml_read, buffer))
        {
        #if defined(__unix)
            for (unsigned int i = 0; i < buffer.size(); i++)
            {
                // Get rid of any carriage returns on Unix (does funny things to console printing)
                if (buffer[i] == 0x0d)
                    buffer[i] = ' ';
            }
        #endif
            file_text += buffer;
        }
        xml_read.close();

        if (validate_xml (file_text))
        {
            // TODO: Read each <game> ... </game> entry into a Rom in imported_data
        }
        else
        {
            std::cerr << "Could not parse " << file_name << "!" << std::endl;
        }
    }

    return false;
}

/**
 * 
 */
bool Xml::validate_xml (const std::string &text)
{
    // Make sure the XML file has both the file header and <header> sections
    return (check_xml_header (text) && get_metadata_header (text));
}

/**
 * 
 */
bool Xml::get_metadata_header (const std::string &text)
{
    std::size_t header_start, header_end;

    header_start = text.find ("<header>");
    header_end = text.find ("</header>");

    // Sanity check
    if ((header_start != std::string::npos) &&
        (header_end != std::string::npos) &&
        (header_start < header_end))
    {
        // Create a substring that only contains <header> ... </header> information
        std::string meta_header = text.substr (header_start, header_end);

        set_name (search_metadata_header ("name", meta_header));
        set_description (search_metadata_header ("description", meta_header));
        set_author (search_metadata_header ("author", meta_header));
        set_homepage (search_metadata_header ("homepage", meta_header));

        return true;
    }

    return false;
}

/**
 * @fn Xml::append_rom
 * @brief Adds a Rom instance to the internal list for Xml
 */
unsigned int Xml::append_rom (const Rom &data)
{
    imported_data.push_back (data);
    return imported_data.size();
}

/**
 * @fn Xml::sort_data
 * @brief Sorts entries in imported_data.
 * @see Overloaded operators for Rom class.
 */
void Xml::sort_data()
{
    sort (imported_data.begin(), imported_data.end());
}

/**
 * @fn Xml::find_crc
 * @brief Binary searches Rom entries for a matching CRC checksum.
 * @pre The imported_data vector should be sorted by CRC.
 * 
 * @see Overloaded operators for Rom class.
 */
Rom Xml::find_crc (std::string crc)
{
    Rom ret_entry = Rom();
    std::string current_crc = "";
    unsigned int low = 0, high = imported_data.size() - 1, avg = 0;

    // Ensure given CRC is all uppercase
    for (unsigned int i = 0; i < crc.size(); i++)
        crc[i] = std::toupper (crc[i]);

    // Binary search to find CRC value specified
    while (low < high)
    {
        avg = (low + high) / 2;
        current_crc = imported_data[avg].get_crc();

        if (current_crc > crc)
            high = (avg - 1);
        else if (current_crc < crc)
            low = (avg + 1);
        else
        {
            ret_entry = imported_data[avg];
            break;
        }
    }

    return ret_entry;
}

/**
 * @fn Xml::find_md5
 * @brief Searches Rom entries for a matching MD5 checksum.
 * 
 * @note Linear searches imported_data as entries are sorted by CRC.
 */
Rom Xml::find_md5 (std::string md5)
{
    Rom ret_entry = Rom();

    // Ensure given MD5 is all uppercase
    for (unsigned int i = 0; i < md5.size(); i++)
        md5[i] = std::toupper (md5[i]);

    // Linear search for given MD5
    for (unsigned int entry = 0; entry < imported_data.size(); entry++)
    {
        if (imported_data[entry].get_md5() == md5)
        {
            ret_entry = imported_data[entry];
            break;
        }
    }

    return ret_entry;
}

/**
 * @fn Xml::find_sha
 * @brief Searches Rom entries for a matching SHA1 checksum.
 * 
 * @note Linear searches imported_data as entries are sorted by CRC.
 */
Rom Xml::find_sha (std::string sha)
{
    Rom ret_entry = Rom();

    // Ensure given SHA1 is all uppercase
    for (unsigned int i = 0; i < sha.size(); i++)
        sha[i] = std::toupper (sha[i]);

    // Linear search for given SHA1
    for (unsigned int entry = 0; entry < imported_data.size(); entry++)
    {
        if (imported_data[entry].get_sha() == sha)
        {
            ret_entry = imported_data[entry];
            break;
        }
    }

    return ret_entry;
}

/**
 * @fn Xml::print_rom
 * @brief Prints a Rom instance given some index.
 */
void Xml::print_rom (unsigned int index)
{
    if (index < imported_data.size())
        imported_data[index].print_hashes();
}

/**
 * @fn Xml::print_header
 * @brief Prints the header metadata relating to a loaded XML file.
 */
void Xml::print_header()
{
    std::cout << "\n[XML Header]"
              << "\nName:        " << name
              << "\nDescription: " << description
              << "\nAuthor:      " << author
              << "\nHomepage:    " << homepage
              << std::endl;
}


// === Functions ===================================================================================


/**
 * @fn check_xml_header
 * @brief Checks to make sure the expected header of XML_HEADER is at the start of the file.
 */
bool check_xml_header (const std::string & text)
{
    return (text.substr (0, XML_HEADER.size()) == XML_HEADER);
}

/**
 * @fn search_metadata_header
 * @brief Searches an XML file for the text contained within a tag.
 */
std::string search_metadata_header (const std::string &tag, const std::string &h_text)
{
    std::size_t t_start, t_end;
    std::string ret_str = "";

    if (((t_start = h_text.find ('<' + tag + '>')) != std::string::npos) &&
        ((t_end = h_text.find ("</" + tag + '>')) != std::string::npos) &&
        (t_start < t_end))
    {
        // tag.size() + 2 = size ('<' + tag + '>'); have to take into account for positions
        ret_str = h_text.substr (t_start + (tag.size() + 2),
                                 t_end - (t_start + (tag.size() + 2)));
    }

    return ret_str;
}
