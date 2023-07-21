#include "files.hpp"
#include "interface.hpp"

#include <iostream>


#if defined(__unix)
// === Unix ========================================================================================

unsigned int gen_dir_index (std::string input_dir, std::vector<Rom>& dir_index)
{
    DIR* dir_ptr;
    struct dirent* dir_entity;
    struct stat f_info;

    // Attempt to open directory for indexing
    if ((dir_ptr = opendir (input_dir.c_str())) != NULL)
    {
        std::string full_path = "";
        while ((dir_entity = readdir (dir_ptr)) != NULL)
        {
            full_path = input_dir + '/' + dir_entity->d_name;

            // Ignore the "." and ".." directories
            if ((full_path == input_dir + "/.") || (full_path == input_dir + "/.."))
                continue;
            
            if (stat (full_path.c_str(), &f_info) == 0)
            {
                // Recurse using gen_dir_index again if path refers to directory
                if (f_info.st_mode & S_IFDIR)
                {
                    gen_dir_index (full_path, dir_index);
                }
                // Add path to list if refers to file
                else if (f_info.st_mode & S_IFREG)
                {
                    dir_index.push_back (Rom(full_path));
                }
            }
        }

        // Indexing operation complete
        closedir (dir_ptr);
    }
    else
    {
        print_error ("Something went wrong trying to open " + input_dir + " as a directory!");
    }

    return dir_index.size();
}


#elif defined(__WIN32)
// === Windows =====================================================================================

// TODO: Test this...
unsigned int gen_dir_index (std::string input_dir, std::vector<Rom>& dir_index)
{
    WIN32_FIND_DATAA dat_find;
    HANDLE f_handle = FindFirstFile ((input_dir + "/*.*").c_str(), &dat_find);

    // Handle didn't find a valid directory
    if (f_handle != INVALID_HANDLE_VALUE)
    {
        std::string dir_name = "";

        do
        {
            // Directory found, recurse so long as directory isn't . or ..
            if (dat_find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                dir_name = dat_find.cFileName; // Cast C-string to C++ string

                if ((dir_name != ".") && (dir_name != ".."))
                {
                    gen_dir_index (input_dir + dir_name + '/', dir_index);
                }
            }
            // File found, add it to the index
            else
            {
                dir_name = input_dir + dat_find.cFileName;
                dir_index.push_back (Rom(dir_name));
            }
        } while (FindNextFile (f_handle, &dat_find));

        FindClose (f_handle);        
    }

    return dir_index.size();
}

#endif