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
            for (unsigned int i = 0; i < buffer.size(); i++)
            {
                if (buffer[i] == '\t')
                    buffer[i] = ' ';
            }
            file_text += buffer;
        }
        xml_read.close();

        validate_xml (file_text);
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


Rom Xml::find_crc (const std::string &crc)
{
    return Rom(); // TODO: Placeholder
}

Rom Xml::find_md5 (const std::string &md5)
{
    return Rom(); // TODO: Placeholder
}

Rom Xml::find_sha (const std::string &sha)
{
    return Rom(); // TODO: Placeholder
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


// === Functions ===================================================================================


/**
 * 
 */
bool validate_xml (const std::string &text)
{
    if (check_xml_header (text) &&
        get_metadata_header (text))
    {
        return true;
    }

    return false;
}

/**
 * 
 */
bool check_xml_header (const std::string & text)
{
    std::string header_text;

    // Make sure the XML header is at the _beginning_ of the file
    header_text = text.substr (0, XML_HEADER.size());

    return (header_text == XML_HEADER);
}

/**
 * 
 */
bool get_metadata_header (const std::string &text)
{
    std::size_t header_start, header_end;

    header_start = text.find ("<header>");
    header_end = text.find ("</header>");

    if ((header_start != std::string::npos) && (header_end != std::string::npos))
    {
        std::string meta_header = text.substr (header_start, header_end);

        
        std::string name, description, author, homepage;

        name = search_metadata_header ("name", meta_header);
        description = search_metadata_header ("description", meta_header);
        author = search_metadata_header ("author", meta_header);
        homepage = search_metadata_header ("homepage", meta_header);

        //std::cout << name << '\n' << description << '\n' << author << '\n' << homepage << '\n';

        return true;
    }

    return false;
}

/**
 * 
 */
std::string search_metadata_header (const std::string &tag, const std::string &h_text)
{
    std::size_t t_start, t_end;
    std::string ret_str = "";

    if (((t_start = h_text.find ('<' + tag + '>')) != std::string::npos) &&
        ((t_end = h_text.find ("</" + tag + '>')) != std::string::npos))
    {
        // tag.size() + 2 = size ('<' + tag + '>'); have to take into account for positions
        ret_str = h_text.substr (t_start + (tag.size() + 2),
                                 t_end - (t_start + (tag.size() + 2)));
    }

    return ret_str;
}
