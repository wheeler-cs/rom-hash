#ifndef FILES_HPP
#define FILES_HPP

#if defined(__unix)

#include "dirent.h"
#include "sys/stat.h"

#elif defined(__WIN32)

#include <Windows.h>

#endif

#include "file.hpp"

#include <string>
#include <vector>


unsigned int gen_dir_index (std::string, std::vector<Rom>&);

#endif