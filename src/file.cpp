#include "file.hpp"

#include <fstream>
#include <iostream>


// === Ctors =======================================================================================

File::File()
{
    // File metadata
    this->file_name = "";
    this->file_size = 0;

    // Hashes
    this->crc = "";
    this->md5 = "";
    this->sha1 = "";
}

File::File (std::string file)
{
    this->file_name = file;
    // Go ahead and calculate hashes and file size
    this->calculate_file_size();
    this->calculate_hashes();
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
    std::ifstream f_size_read (file_name.c_str());
    if (f_size_read.is_open())
    {
        /**
         * Note: This method *should* be cross-platform, but I make no guarantees. At the very
         * least it doesn't require setting up defines at the moment for Windows/Linux differences.
         * "Under the hood" implementation of seekg/tellg may make this not work right for you.
         */
        f_size_read.seekg (0, std::ios::end);
        this->file_size = (uint64_t) f_size_read.tellg();
        f_size_read.close();                        
    }
    else
    {
        // Default to a file size of 0 if a stream cannot be opened
        this->file_size = 0;
    }
}

/**
 * @brief Prints metadata and hash information about a file.
 */
void File::print_hashes() const
{
    std::cout << "\nFile: " << this->file_name
              << "\nSize: " << this->file_size
              << "\n CRC: " << this->crc
              << "\nSHA1: " << this->sha1
              << "\n MD5: " << this->md5
              << std::endl;
}


// === Operator overloads ==========================================================================


/**
 * @overload ==
 */
bool operator== (const File& a, const File& b)
{
    /*
     * CRC, MD5, SHA1, and file size should match; file names do not necessarily have to match as
     * this is looking for metadata equality as opposed to literal equality
     */
    if ((a.crc == b.crc) &&
        (a.md5 == b.md5) &&
        (a.sha1 == b.sha1) &&
        (a.file_size == b.file_size))
    {
        return true;
    }
    else
    {
        return false;
    }

}

/**
 * @overload >
 */
bool operator> (const File& a, const File& b)
{
    /*
     * Attributes are evaluated in the following order:
     *  -CRC
     *  -MD5
     *  -SHA1
     *  -File size
     */
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
                if (a.file_size > b.file_size)
                    return true;
            }
        }
    }
    
    return false;
}

/**
 * @overload <
 */
bool operator< (const File& a, const File& b)
{
    /*
     * Attributes are evaluated in the following order:
     *  -CRC
     *  -MD5
     *  -SHA1
     *  -File size
     */
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
                if (a.file_size < b.file_size)
                    return true;
            }
        }
    }
    
    return false;
}
