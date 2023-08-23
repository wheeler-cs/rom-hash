#include "file.hpp"
#include "hash.hpp"

#include <fstream>
#include <iostream>


// === Ctors =======================================================================================

File::File()
{
    // File metadata
    this->name = "";
    this->binary_size = 0;

    // Hashes
    this->crc = "";
    this->md5 = "";
    this->sha1 = "";
}

File::File (std::string file)
{
    this->name = file;
    // Go ahead and calculate hashes and file size
    this->calculate_file_size();
    this->calculate_hashes();
}

File::File (std::vector <std::pair <std::string, std::string>> attributes)
{
    for (unsigned int i = 0, a_size = attributes.size(); i < a_size; i++)
    {
        // This feels wrong... but I don't know of another way of comparing a lot of strings...
        if (attributes[i].first == "name")
            this->name = attributes[i].second;
        else if (attributes[i].first == "size")
            this->binary_size = std::stoi (attributes[i].second); // TODO: Exception-handle this
        else if (attributes[i].first == "crc")
            this->crc = attributes[i].second;
        else if (attributes[i].first == "md5")
            this->md5 = attributes[i].second;
        else if (attributes[i].first == "sha1")
            this->sha1 = attributes[i].second;
    }
}


// === Member methods ==============================================================================


/**
 * @brief Calculates CRC, SHA1, and MD5 hashes for a given file.
 */
bool File::calculate_hashes()
{

    // TODO: Reimplement this

    return false;
}

/**
 * @brief Gets the size of a file by using an ifstream.
 */
void File::calculate_file_size()
{
    // Open a file stream and try to calculate size from std::ios::end
    std::ifstream f_size_read (this->name.c_str());
    if (f_size_read.is_open())
    {
        /**
         * Note: This method *should* be cross-platform, but I make no guarantees. At the very
         * least it doesn't require setting up defines at the moment for Windows/Linux differences.
         * "Under the hood" implementation of seekg/tellg may make this not work right for you.
         */
        f_size_read.seekg (0, std::ios::end);
        this->binary_size = (uint64_t) f_size_read.tellg();
        f_size_read.close();                        
    }
    else
    {
        // Default to a file size of 0 if a stream cannot be opened
        this->binary_size = 0;
    }
}

/**
 * @brief Prints metadata and hash information about a file.
 */
void File::print_hashes() const
{
    std::cout << "\nFile: " << this->name
              << "\nSize: " << this->binary_size
              << "\n CRC: " << this->crc
              << "\nSHA1: " << this->sha1
              << "\n MD5: " << this->md5
              << std::endl;
}


// === Operator overloads ==========================================================================


/**
 * @overload ==
 * 
 * @brief Checks each attribute of the two File classes, excluding name, and returns if all of those
 *        values are equal.
 * 
 * @param a An instance of the File class.
 * @param b An instancce of the File class.
 * 
 * @returns If all hashes and binary file size of the two parameters are the same.
 */
bool operator== (const File& a, const File& b)
{
    return ((a.crc == b.crc) &&
            (a.md5 == b.md5) &&
            (a.sha1 == b.sha1) &&
            (a.binary_size == b.binary_size));
}

/**
 * @overload >
 * 
 * @brief "Compares" two File class instances and determines which is "greater than" the other.
 * 
 * The functionality of this operator is needed if a list of File class instances are to be sorted.
 * 
 * @param a An instance of the File class.
 * @param b An instance of the File class.
 * 
 * @returns The evaluation of if a is "greater than" b.
 * 
 * @note Attributes are evaluated in this order: crc, md5, sha1, binary_size.
 */
bool operator> (const File& a, const File& b)
{
    if (a.crc > b.crc)
        return true;
    else if (a.crc == b.crc)
    {
        if (a.md5 > b.md5)
            return true;
        else if (a.md5 == b.md5)
        {
            if (a.sha1 > b.sha1)
                return true;
            else if (a.sha1 == b.sha1)
            {
                if (a.binary_size > b.binary_size)
                    return true;
            }
        }
    }
    
    return false;
}

/**
 * @overload <
 * 
 * @brief "Compares" two File class instances and determines which is "less than" the other.
 * 
 * The functionality of this operator is needed if a list of File class instances are to be sorted.
 * 
 * @param a An instance of the File class.
 * @param b An instance of the File class.
 * 
 * @returns The evaluation of if a is "less than" b.
 * 
 * @note Attributes are evaluated in this order: crc, md5, sha1, binary_size.
 */
bool operator< (const File& a, const File& b)
{
    if (a.crc < b.crc)
        return true;
    else if (a.crc == b.crc)
    {
        if (a.md5 < b.md5)
            return true;
        else if (a.md5 == b.md5)
        {
            if (a.sha1 < b.sha1)
                return true;
            else if (a.sha1 == b.sha1)
            {
                if (a.binary_size < b.binary_size)
                    return true;
            }
        }
    }
    
    return false;
}
