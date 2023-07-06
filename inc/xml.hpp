#ifndef XML_HPP
#define XML_HPP

#include "rom.hpp"

#include <algorithm>
#include <vector>


class Xml
{
public:
    // Ctors
    Xml() {};

    // Mutators
    void set_imported_data (const std::vector<Rom> data) { imported_data = data; }

    // Accessors
    std::vector<Rom> get_imported_data() const { return imported_data; }

    // Member methods
    unsigned int append_rom (const Rom &);
    void sort_data();
    Rom find_crc (const std::string &);
    Rom find_md5 (const std::string &);
    Rom find_sha (const std::string &);
    void print_rom (unsigned int);


private:
    std::vector <Rom> imported_data;
};

#endif