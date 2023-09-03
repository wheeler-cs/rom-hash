#include "xml.hpp"

#include <fstream>
#include <iostream>


// === Ctors =======================================================================================

/**
 * @brief Initializes an instance of Xml class by using a specific file as input.
 */
Xml::Xml (const std::string &file_name)
{
    this->import_xml (file_name);
}


// === Accessors ===================================================================================

/**
 * @brief Returns the data of the File entry at the given index.
 * 
 * @param idx The index of the File data to be pulled from the list the Xml instance stores.
 * 
 * @returns A File class instance.
 * @retval `File()` is returned if provided index is too large for internal `file_entries` list.
 */
File Xml::get_file_entry (unsigned int idx)
{
    if (idx < this->file_entries.size())
        return this->file_entries[idx];
    else
        return File();
}

/**
 * @brief Linearly searches for the supplied tag in the list of header data.
 * 
 * @param query_tag The tag to search for within header_data
 * 
 * @returns The data associated with the given tag, or the empty string if the tag isn't found.
 */
std::string Xml::get_tag (const std::string &query_tag)
{
    std::string ret_string = "";
    for (unsigned int i = 0, limit = this->header_data.size(); i < limit; i++)
    {
        if (query_tag == this->header_data[i].first)
            ret_string = this->header_data[i].second;
    }

    return ret_string;
}


// === Mutators ====================================================================================

/**
 * @brief Resets the member data of the calling Xml class. This is often done when new data is to be
 *        imported.
 */
void Xml::reset()
{
    this->header_data.clear();
}


// === Member methods ==============================================================================

/**
 * @brief Validates, then loads the contents of, an XML file.
 * 
 * @param f_name Name of the file to be imported.
 * 
 * @returns The success status of the import operation.
 * 
 * @todo Wrap some of the code here up into functions.
 */
bool Xml::import_xml (const std::string &f_name)
{
    this->reset();

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
    xml_read.close(); // Done with file buffer

    // Preprocess text to remove certain characters that can be problematic
    for (unsigned int i = 0, xml_len = xml_text.size(); i < xml_len; i++)
    {
        // NOTE: 0x15 is carridge return
        if ((xml_text[i] == 0x15) || (xml_text[i] == '\n') || (xml_text[i] == '\t'))
            xml_text[i] = ' ';
    }

    // Validate that XML text is usable
    if (!(validate_xml (xml_text)))
        return false;

    // Create index of header data (if header data exists)
    std::vector <std::string> header_tags;
    std::string header_contents = get_element_content (xml_text, "header", false);
    if (header_contents != "")
        this->process_header_data (header_contents);

    // Index where each <game> block is and extract the data within
    std::vector <unsigned int> block_starts = subdivide_xml (xml_text, "game", true);
    std::string block_data = "";
    std::vector <std::pair <std::string, std::string>> attribute_data;
    for (unsigned int i = 0, v_size = block_starts.size(); i < v_size; i++)
    {
        block_data = xml_text.substr (block_starts[i], (block_starts[i+1] - block_starts[i]));
        attribute_data = get_attributes (block_data, "rom");
        this->file_entries.push_back (File (attribute_data));   // New File instance with data
    }

    return true;
}


/**
 * @brief Load the element contents for each header tag into the calling instance's header_data.
 * 
 * @param header_content The XML-formatted text of the header that contains tags to be extracted.
 */
void Xml::process_header_data (const std::string &header_content)
{
    // Get a list of tags in the header text
    std::vector <std::string> tag_list = generate_tag_list (header_content);
    if (tag_list.size() == 0)
        return;

    std::string tag_content = "";
    // Extract element content text associated with tags
    for (unsigned int i = 0, list_size = tag_list.size(); i < list_size; i++)
    {
        tag_content = get_element_content (header_content, tag_list[i], true);
        if (tag_content != "")
        {
            std::pair <std::string, std::string> tag_data (tag_list[i], tag_content);
            this->header_data.push_back (tag_data); // New tag added
        }
    }
}


/**
 * @brief Iterates through and prints out each tag and it's associated content stored in the
 *        header_data vector of the calling instance.
 */
void Xml::print_header_data()
{
    for (unsigned int i, list_size = this->header_data.size(); i < list_size; i++)
    {
        std::cout << this->header_data[i].first << " | " << this->header_data[i].second << '\n';
    }
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


/**
 * @brief Returns the raw text content stored between two tags.
 * 
 * @param xml_text The XML text containing the subtext to extract.
 * @param tag The tags that contain the desired text.
 * @param ignore_attributes If attributes should be ignored for the start tag.
 * 
 * @returns A string composed of the text found as part of an XML element. If the tag given cannot
 *          be resolved, the null string is returned instead.
 */
std::string get_element_content (const std::string &xml_text, const std::string &tag, bool ignore_attributes)
{
    // HACK: This is an easy way force inclusion or exclusion of tags with attributes
    std::string tag_start = "";
    if (ignore_attributes)
        tag_start = "<" + tag;
    else
        tag_start = "<" + tag + ">";
    const std::string tag_end = "</" + tag + ">";

    // Look for the start and end tags
    size_t start_pos = 0, end_pos = 0;
    start_pos = xml_text.find (tag_start, 0);
    if (start_pos == std::string::npos)
        return "";
    end_pos = xml_text.find (tag_end, start_pos);
    if (end_pos == std::string::npos)
        return "";

    // Set start position to location of '>' for start tag; ignoring attributes requires finding
    // the next instance of that character, which means skipping over the attributes of the tag
    if (ignore_attributes)
    {
        for (unsigned int i = start_pos; i < end_pos; i++)
        {
            if (xml_text[i] == '>')
            {
                start_pos = i + 1; // Incr. by 1 to align correctly
                break;
            }
        }
    }
    else
        start_pos += tag_start.size();

    // Return the substring of data stored between the tag's open and close
    return (xml_text.substr (start_pos, (end_pos - start_pos)));
}


/**
 * @brief Obtains a list of tags found in the XML text passed in.
 * 
 * @param text Some XML text with a number of tags.
 * 
 * @returns A vector of strings containing all of the tags found in the given text.
 */
std::vector <std::string> generate_tag_list (const std::string &text)
{
    std::vector <std::string> tag_list;

    // Linear search through text to find all tags
    unsigned int text_length = text.size();
    for (unsigned int i = 0; i < text_length; i++)
    {
        // Add tag text if tag found is a start tag
        if ((text[i] == '<') && (text[i + 1] != '/'))
        {
            std::string tag = "";
            // Linear search from start tag until end of tag name
            for (unsigned int j = i + 1; j < text_length; j++)
            {
                if ((text[j] == '>') || (text[j] == '/') || (text[j] == ' '))
                    break;
                else
                    tag += text[j];
            }

            tag_list.push_back (tag);
            i += tag.size();
        }
    }
    return tag_list;
}


/**
 * @brief Subdivides the content of an XML file into blocks by creating a list of positions where a
 *        given start tag can be found in the text.
 * @param xml_text The raw XML-formatted text to be searched.
 * @param tag The value of the start tag to be searched for.
 * @param ignore_attributes Whether attributes should be ignored when searching for the start tag,
 *        or the <tag> should be searched for verbatium.
 * 
 * @returns A vector containing the indices of where the tag can be found within the text.
 * 
 */
std::vector <unsigned int> subdivide_xml (const std::string &xml_text, const std::string &tag, bool ignore_attributes)
{
    // Do not search for the '>' if ignoring attributes
    std::string tag_start = "";
    if (ignore_attributes)
        tag_start = '<' + tag;
    else
        tag_start = '<' + tag + '>';

    std::vector <unsigned int> block_locations;
    size_t block_start = 0;

    // Search for all instances of <tag> and generate an index
    block_start = xml_text.find (tag_start, block_start);
    while (block_start != std::string::npos)
    {
        block_locations.push_back ((unsigned int) block_start);
        block_start = xml_text.find (tag_start, block_start + 1);
    }

    return block_locations;
}


/**
 * @brief Searches the given text for tag specified, and, if found, extracts all attributes from
 *        the start tag.
 * 
 * @param xml_text The XML-format text to be searched.
 * @param tag The tag containing the parameters to be extracted.
 * 
 * @returns A vector of attribute-value pairs associated with the given tag.
 */
std::vector <std::pair <std::string, std::string>> get_attributes (const std::string &xml_text, const std::string &tag)
{
    std::vector <std::pair <std::string, std::string>> attributes;
    std::string tag_string = "";
    size_t tag_start = 0, tag_end = 0;

    // Locate where in the text the tag is contained
    tag_start = xml_text.find ('<' + tag, 0);
    if (tag_start == std::string::npos)
        return attributes;
    tag_end = xml_text.find ('>', tag_start + 1);
    if (tag_end == std::string::npos)
        return attributes;

    // Iterate through tag text and extract each attribute, assuming format of attr=val
    std::string attribute = "", value = "";
    size_t val_start = 0, val_end = 0;
    for (unsigned int i = tag_start; i < tag_end; i++)
    {
        if (xml_text[i] == ' ')
        {
            // Get the attribute name
            val_start = xml_text.find ('\"', i);
            if (val_start == std::string::npos)
                break;
            attribute = xml_text.substr (i + 1, (val_start - (i + 2)));

            // Get the attribute value
            val_end = xml_text.find ('\"', val_start + 1);
            if (val_end == std::string::npos)
                break;
            value = xml_text.substr (val_start + 1, (val_end - (val_start + 1)));

            // Increment i to move past the attribute that was just read
            i += (val_end - val_start);

            std::pair <std::string, std::string> attribute_data (attribute, value);
            attributes.push_back (attribute_data);
        }
    }

    return attributes;
}
