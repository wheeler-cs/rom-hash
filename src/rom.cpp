#include "rom.hpp"

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

        return true;
    }
    // Something really bad happened...
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
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
void Rom::print_hashes()
{
    std::cout << "\nFile: " << file_name
              << "\nSize: " << file_size
              << "\n CRC: " << crc
              << "\nSHA1: " << sha1
              << "\n MD5: " << md5
              << std::endl;
}
