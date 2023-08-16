#include "xml.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    Xml xml_file;
    std::string arg = argv[1];
    xml_file.import_xml (arg);
    //std::cout << xml_file.get_tag ("name");

    std::cout << std::endl;
    return 0;
}