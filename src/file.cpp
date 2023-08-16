#include "file.hpp"

#include <fstream>
#include <iostream>


// === Ctors =======================================================================================

Rom::Rom()
{
    // File metadata
    file_name = "";
    file_size = 0;

    // Hashes
    crc = "";
    md5 = "";
    sha1 = "";
}

Rom::Rom (std::string file)
{
    file_name = file;
    // Go ahead and calculate hashes and file size
    calculate_file_size();
    calculate_hashes();
}


// === Member methods ==============================================================================


/**
 * @fn Rom::calculate_hashes
 * @brief Calculates CRC, SHA1, and MD5 hashes for a given file.
 */
bool Rom::calculate_hashes()
{
    /*
    try
    {
        // Hash classes for calculating each hash
        CryptoPP::CRC32 crc_hash;
        CryptoPP::SHA1 sha_hash;
        CryptoPP::Weak::MD5 md5_hash;

        // Associate each class hash with a filter
        CryptoPP::HashFilter crc_filter (crc_hash, new CryptoPP::HexEncoder (new CryptoPP::StringSink (crc)));
        CryptoPP::HashFilter sha_filter (sha_hash, new CryptoPP::HexEncoder (new CryptoPP::StringSink (sha1)));
        CryptoPP::HashFilter md5_filter (md5_hash, new CryptoPP::HexEncoder (new CryptoPP::StringSink (md5)));

        // Add each hash to the channel switch for passing data blocks in parallel
        CryptoPP::ChannelSwitch c_switch;
        c_switch.AddDefaultRoute (crc_filter);
        c_switch.AddDefaultRoute (sha_filter);
        c_switch.AddDefaultRoute (md5_filter);

        // Specify the file as a source and calculate hashes
        CryptoPP::FileSource (file_name.c_str(), true, new CryptoPP::Redirector (c_switch));

        // Convert endian-ness of CRC
        std::string bigram_a = "", bigram_b = "";

        for (unsigned int i = 0; i < crc.size() / 2; i += 2)
        {
            bigram_a = crc[i];
            bigram_a += crc[i + 1];

            bigram_b = crc[crc.size() - (2 + i)];
            bigram_b += crc[crc.size() - (1 + i)];

            crc[i] = bigram_b[0];
            crc[i + 1] = bigram_b[1];

            crc[crc.size() - (2 + i)] = bigram_a[0];
            crc[crc.size() - (1 + i)] = bigram_a[1];
        }


        return true;
    }
    // Something really bad happened...
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    */
    return false;
}

/**
 * @fn Rom::calculate_file_size
 * @brief Gets the size of a file by using an ifstream.
 */
void Rom::calculate_file_size()
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
        file_size = (uint64_t) f_size_read.tellg();
        f_size_read.close();                        
    }
    else
    {
        // Default to a file size of 0 if a stream cannot be opened
        file_size = 0;
    }
}

/**
 * @fn Rom::print_hashes
 * @brief Prints metadata and hash information about a file.
 */
void Rom::print_hashes() const
{
    std::cout << "\nFile: " << file_name
              << "\nSize: " << file_size
              << "\n CRC: " << crc
              << "\nSHA1: " << sha1
              << "\n MD5: " << md5
              << std::endl;
}


// === Operator overloads ==========================================================================


/**
 * @overload ==
 */
bool operator== (const Rom& a, const Rom& b)
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
bool operator> (const Rom& a, const Rom& b)
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
bool operator< (const Rom& a, const Rom& b)
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
