#ifndef FILE_HPP
#define FILE_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>


class File
{
public:
    // Ctors
    File();
    File (std::string);
    File (std::vector <std::pair <std::string, std::string>>);

    // Mutators; sets member variables
    void set_file_name (const std::string &f_name)  { this->name = f_name; }
    void set_file_size (const uint64_t &f_size)     { this->binary_size = f_size; }
    void set_crc (const std::string &hash)          { this->crc = hash; }
    void set_md5 (const std::string &hash)          { this->md5 = hash; }
    void set_sha1 (const std::string &hash)         { this->sha1 = hash; }

    // Accessors; gets member variables
    std::string get_file_name() const { return this->name; }
    uint64_t get_file_size() const    { return this->binary_size; }
    std::string get_crc() const       { return this->crc; }
    std::string get_md5() const       { return this->md5; }
    std::string get_sha1() const      { return this->sha1; }

    // Member methods
    bool calculate_hashes();
    void calculate_file_size();
    void print_hashes() const;

    // Operator overloads (as friends); allows using things such as "sort" with class
    friend bool operator== (const File&, const File&);
    friend bool operator>  (const File&, const File&);
    friend bool operator<  (const File&, const File&);

private:
    // Basic file data
    std::string name;
    unsigned int binary_size;

    // Hashes for file
    std::string crc, md5, sha1;

};


bool operator== (const File&, const File&);
bool operator>  (const File&, const File&);
bool operator<  (const File&, const File&);

#endif