#ifndef ROM_HPP
#define ROM_HPP

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cstdint>
#include <string>


class Rom
{
public:
    // Ctors
    Rom();
    Rom (std::string);

    // Mutators; sets member variables
    void set_file_name (std::string f_name)  { file_name = f_name; }
    void set_file_size (uint64_t f_size)     { file_size = f_size; }
    void set_crc (std::string hash)          { crc = hash; }
    void set_md5 (std::string hash)          { md5 = hash; }
    void set_sha1 (std::string hash)         { sha1 = hash; }

    // Accessors; gets member variables
    std::string get_file_name()  { return file_name; }
    uint64_t get_file_size()     { return file_size; }
    std::string get_crc()        { return crc; }
    std::string get_md5()        { return md5; }
    std::string get_sha1()       { return sha1; }

    // Member methods
    bool calculate_hashes();
    void calculate_file_size();
    void print_hashes();

private:
    // File metadata
    std::string file_name;  // Name of the file of the ROM associated with class
    uint64_t file_size; // Size of file (in bytes)

    // Hashes
    std::string crc;
    std::string sha1;
    std::string md5;

};

#endif