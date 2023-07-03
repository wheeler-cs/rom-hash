#include "rom.hpp"

Rom::Rom()
{
    // File metadata
    file_name = "";
    file_size = 0;

    // Hashes
    crc = "";
    md5 = "";
    sha1 = "";
}


bool Rom::calculate_hashes()
{
    CryptoPP::CRC32 crc_hash;
    CryptoPP::SHA1 sha1_hash;
    CryptoPP::HashFilter crc_filter (crc_hash, new CryptoPP::HexEncoder (new CryptoPP::StringSink (crc)));
    CryptoPP::HashFilter sha_filter (sha1_hash, new CryptoPP::HexEncoder (new CryptoPP:StringSink (sha)));

    CryptoPP::ChannelSwitch c_switch;
    c_switch.AddDefaultRoute (crc_filter);
    c_switch.AddDefaultRoute (sha_filter);

    CryptoPP::FileSource (file_name.c_str(), true, new CryptoPP::Redirector (c_switch));
}