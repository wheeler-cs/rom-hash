#include "xml.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    Xml xml_file;
    std::cout << xml_file.import_xml ("hashes/GameBoyAdvance.dat");

    return 0;
}