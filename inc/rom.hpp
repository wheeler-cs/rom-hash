#ifndef ROM_HPP
#define ROM_HPP

#include <string>

#include "cryptopp/channels.h"
#include "cryptopp/crc.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha.h"


class Rom
{
public:
    // Ctors
    Rom();

    // Mutators; sets member variables
    void set_file_name (std::string f_name)  { file_name = f_name; }
    void set_file_size (unsigned int f_size) { file_size = f_size; }
    void set_crc (std::string hash)          { crc = hash; }
    void set_md5 (std::string hash)          { md5 = hash; }
    void set_sha1 (std::string hash)         { sha1 = hash; }

    // Accessors; gets member variables
    std::string get_file_name()  { return file_name; }
    unsigned int get_file_size() { return file_size; }
    std::string get_crc()        { return crc; }
    std::string get_md5()        { return md5; }
    std::string get_sha1()       { return sha1; }

    // Member methods
    bool calculate_hashes();

private:
    // File metadata
    std::string file_name;  // Name of the file of the ROM associated with class
    unsigned int file_size; // Size of file (in bytes)

    // Hashes
    std::string crc;
    std::string md5;
    std::string sha1;
};

#endif