#include "xml.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    Xml xml_file;
    xml_file.import_xml ("hashes/GameBoyAdvance.dat");
    std::cout << xml_file.get_tag ("name");

    return 0;
}