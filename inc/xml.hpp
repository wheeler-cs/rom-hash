#ifndef XML_HPP
#define XML_HPP

#include "rom.hpp"

#include <algorithm>
#include <vector>


// === Constants ===================================================================================


/**
 * Typical header of XML dat files containing hash data. Should be the first line of the file.
 */
static const std::string XML_HEADER = "<?xml version=\"1.0\"?>";


// === Class definitions ===========================================================================


class Xml
{
public:
    // Ctors
    Xml() {};

    // Mutators
    void set_imported_data (const std::vector<Rom> data) { imported_data = data; }

    // Accessors
    std::vector<Rom> get_imported_data() const { return imported_data; }

    // Member methods
    bool import_xml (const std::string &);
    unsigned int append_rom (const Rom &);
    void sort_data();
    Rom find_crc (const std::string &);
    Rom find_md5 (const std::string &);
    Rom find_sha (const std::string &);
    void print_rom (unsigned int);


private:
    std::string file_name;

    std::string name, description, author, homepage;

    std::vector <Rom> imported_data;
};


bool validate_xml (const std::string &);
bool check_xml_header (const std::string &);
bool get_metadata_header (const std::string &);
std::string search_metadata_header (const std::string &, const std::string &);

#endif