#ifndef FILES_HPP
#define FILES_HPP

#if defined(__unix)

#include "dirent.h"
#include "sys/stat.h"

#elif defined(__WIN32)

// ~ Windows API headers go here ~

#endif

#include <iostream>
#include <string>
#include <vector>


unsigned int gen_dir_index (std::string, std::vector<std::string>&);

#endif