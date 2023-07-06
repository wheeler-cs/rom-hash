#include "xml.hpp"


// === Ctors =======================================================================================


// === Member methods ==============================================================================

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
