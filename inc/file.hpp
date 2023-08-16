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
    void set_file_name (const std::string &f_name)  { file_name = f_name; }
    void set_file_size (const uint64_t &f_size)     { file_size = f_size; }
    void set_crc (const std::string &hash)          { crc = hash; }
    void set_md5 (const std::string &hash)          { md5 = hash; }
    void set_sha (const std::string &hash)          { sha1 = hash; }

    // Accessors; gets member variables
    std::string get_file_name() const { return file_name; }
    uint64_t get_file_size() const    { return file_size; }
    std::string get_crc() const       { return crc; }
    std::string get_md5() const       { return md5; }
    std::string get_sha() const       { return sha1; }

    // Member methods
    bool calculate_hashes();
    void calculate_file_size();
    void print_hashes() const;

    // Operator overloads (as friends); allows using things such as "sort" with class
    friend bool operator== (const Rom&, const Rom&);
    friend bool operator> (const Rom&, const Rom&);
    friend bool operator< (const Rom&, const Rom&);

private:
    // File metadata
    std::string file_name;  // Name of the file of the ROM associated with class
    uint64_t file_size; // Size of file (in bytes)

    // Hashes
    std::string crc;
    std::string sha1;
    std::string md5;

};


bool operator== (const Rom&, const Rom&);
bool operator> (const Rom&, const Rom&);
bool operator< (const Rom&, const Rom&);

#endif