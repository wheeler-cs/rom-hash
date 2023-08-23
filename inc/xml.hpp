#ifndef XML_HPP
#define XML_HPP

#include "file.hpp"

#include <algorithm>
#include <cctype>
#include <utility>
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
    Xml (const std::string &);

    // Accessors
    std::string get_tag (const std::string &);

    // Mutators
    void reset();

    // Member methods
    bool import_xml (const std::string &);
    void process_header_data (const std::string &);

    // Print methods
    void print_header_data();

private:
    std::vector <std::pair <std::string, std::string>> header_data;

    std::vector <File> file_entries;
};


bool validate_xml (const std::string &);
bool check_xml_signature (const std::string &);
bool check_tag (const std::string &, const std::string &, bool);
std::string get_element_content (const std::string &, const std::string &, bool);
std::vector <std::string> generate_tag_list (const std::string &);
std::vector <unsigned int> subdivide_xml (const std::string &, const std::string &, bool);
std::vector <std::pair <std::string, std::string>> get_attributes (const std::string &, const std::string &);

#endif