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
    return (check_xml_signature (xml_text) &&
            check_tag (xml_text, "datafile", true));
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
bool check_xml_signature (const std::string &xml_text)
{
    std::string test_signature = xml_text.substr (0, XML_SIGNATURE.size());

    return (test_signature == XML_SIGNATURE);
}


/**
 * @brief Checks for the presence of a given tag.
 * 
 * @param xml_text The XML text to be searched.
 * @param tag The tag to be searched for.
 * @param ignore_attributes If attributes after the start tag should be ignored.
 * 
 * @note The tag should just be the text contained within and not include the tag start or tag end
 *       brackets.
 * 
 * @returns If the tag specified is found in the given text and if the start and end tags
 *          corresponding to it are in valid positions.
 */
bool check_tag (const std::string &xml_text, const std::string &tag, bool ignore_attributes)
{
    // HACK: This is an easy way force inclusion or exclusion of tags with attributes
    std::string tag_start = "";
    if (ignore_attributes)
        tag_start = "<" + tag;
    else
        tag_start = "<" + tag + ">";
    const std::string tag_end = "</" + tag + ">";

    // Look for the start and end tags
    unsigned int start_pos = 0, end_pos = 0;
    start_pos = xml_text.find(tag_start, 0);
    end_pos = xml_text.find (tag_end, 0);

    // Check failed if start or end tag could not be found OR start tag was found after end tag
    if ((start_pos == std::string::npos) || (end_pos == std::string::npos) || (start_pos >= end_pos))
        return false;
    
    return true;
}
