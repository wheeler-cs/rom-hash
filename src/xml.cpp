#include "xml.hpp"

#include <fstream>
#include <iostream>


// === Ctors =======================================================================================


// === Member methods ==============================================================================

/**
 * @brief Validates, then loads the contents of, an XML file.
 * 
 * @param f_name Name of the file to be imported.
 * 
 * @returns The success status of the import operation.
 */
bool Xml::import_xml (const std::string &f_name)
{
    // Open file stream for XML file
    std::ifstream xml_read (f_name.c_str());
    if (!(xml_read.is_open()))
        return false;
    xml_read >> std::noskipws;  // NOTE: Don't skip whitespace

    // Load file text into memory
    std::string xml_text = "", buffer_str = "";
    while (getline (xml_read, buffer_str))
    {
        xml_text += buffer_str;
    }
    xml_read.close();

    // Validate that XML text is usable
    if (!(validate_xml (xml_text)))
        return false;

    return true;
}


// === Functions ===================================================================================

/**
 * @brief Evaluates the contents of an imported XML file for valid formatting and expected sections.
 * 
 * @param xml_text An XML file, stored in its entirety as a C++ string.
 * 
 * @returns The validity of the XML text provided.
 * 
 * @related Xml
 */
bool validate_xml (const std::string &xml_text)
{
    return (check_xml_signature (xml_text));
}

/**
 * @brief Checks for the presence of an XML signature in the file text.
 * 
 * @param xml_text An XML file, stored as a C++ string.
 * 
 * @returns The presence or absence of the XML file signature.
 * 
 * @see XML_SIGNATURE
 */
bool check_xml_signature (const std::string & xml_text)
{
    std::string test_signature = xml_text.substr (0, XML_SIGNATURE.size());

    return (test_signature == XML_SIGNATURE);
}
