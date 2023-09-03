#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <string>


class ProgramFlags
{
public:
    // Ctors
    ProgramFlags();
    ProgramFlags (int, char**);
    ProgramFlags (std::string, std::string, bool);

    // Accessors; sets member variables
    void set_silence (bool flag)        { is_silent = flag; }
    void set_rom_dir (std::string dir)  { rom_dir = dir; }
    void set_hash_dir (std::string dir) { hash_dir = dir; }
    void set_exit_state (bool flag)     { exit_state = flag; }

    // Mutators; gets member variables
    bool get_silence()         { return is_silent; }
    std::string get_rom_dir()  { return rom_dir; }
    std::string get_hash_dir() { return hash_dir; }
    bool get_exit_state()      { return exit_state; }

    // Member methods
    void handle_arguments (int, char**);

private:
    // Flags
    bool is_silent; // Program will only print out non-matching hashes

    // Directories
    std::string rom_dir;    // Directory containing roms to check
    std::string hash_dir;   // Directory containing files with rom hashes

    // Error-related
    bool exit_state;       // Severe error in program has been encountered _OR_ exit should occur
};

#endif