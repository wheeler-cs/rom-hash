#ifndef XML_HPP
#define XML_HPP

#include "rom.hpp"

#include <algorithm>
#include <cctype>
#include <vector>


// === Constants ===================================================================================


/**
 * Typical signature of XML dat files containing hash data. Should be the first line of the file.
 */
static const std::string XML_SIGNATURE = "<?xml version=\"1.0\"?>";


// === Class definitions ===========================================================================


class Xml
{
public:
    // Ctors
    Xml() {};

    // Mutators
    void set_name (const std::string &xml_name) { name = xml_name; }
    void set_description (const std::string &xml_desc) { description = xml_desc; }
    void set_author (const std::string &xml_author) { author = xml_author; }
    void set_homepage (const std::string &xml_homepage) { homepage = xml_homepage; }
    void set_imported_data (const std::vector<Rom> data) { imported_data = data; }

    // Accessors
    std::vector<Rom> get_imported_data() const { return imported_data; }

    // Member methods
    bool import_xml (const std::string &);


private:
    std::string name, description, author, homepage;

    std::vector <Rom> imported_data;
};


bool validate_xml (const std::string &);
bool check_xml_signature (const std::string &);
bool check_tag (const std::string &, const std::string &, bool);

#endif