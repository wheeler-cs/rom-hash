/**
 * @note Algorithms for calculating the CRC32 values were derived from code found at Wikipedia:
 *       https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks#CRC-32_algorithm
 */

#include "hash.hpp"

/**
 * @brief Reads in the data of a file in order to calculate its corresponding CRC32 value.
 * 
 * @param f_name Name of file to be hashed.
 * 
 * @returns The calculated CRC32 hash of the provided file or 0x00000000 in the event of failure.
 * 
 * @retval 0x00000000 Unable to open file provided, for one reason or another.
 */
uint32_t calc_crc32_file (const std::string &f_name)
{
	std::ifstream bin_read (f_name.c_str(), std::ios::binary);

	// Error trying to open file, return all-zero hash
	if (bin_read.fail())
		return 0x00000000;
	// Stream opened, ensure it reads whitespace for hashing
	else
		bin_read >> std::noskipws;

	// Vars used for CRC calculation
	uint32_t crc = 0xffffffff;
	uint8_t byte_buffer = 0x00;
	unsigned int ref_idx = 0;

	// Do calculation
	while (bin_read >> byte_buffer)
	{
		ref_idx = (crc ^ byte_buffer) & 0xff;
		crc = (crc >> 8) ^ CRC_LOOKUP_TABLE[ref_idx];
	}
	bin_read.close();

	// Flip bits and return CRC
	return (crc ^= 0xffffffff);	
}


/**
 * @brief Calculates the CRC32 value of an ASCII string.
 * 
 * @param input The string to have its hash calculated.
 * 
 * @returns The CRC32 hash of the provided string.
 */
uint32_t calc_crc32_str (const std::string &input)
{
	uint32_t crc = 0xffffffff;
	// Store len(input) in var to prevent mult calls to .size()
    unsigned int ref_idx = 0, str_len = input.size();

	for (unsigned int i = 0; i < str_len; i++)
	{
		ref_idx = (crc ^ input[i]) & 0xff;
		crc = (crc >> 8) ^ CRC_LOOKUP_TABLE[ref_idx];  // CRCTable is an array of 256 32-bit constants
	}

	// Return CRC, but invert bits first	
	return (crc ^= 0xffffffff);
}


/**
 * 
 */
__uint128_t calc_md5_str (const std::string &input)
{
	// A, B, C, D
	uint32_t a_ref, b_ref, c_ref, d_ref;
	a_ref = 0x67452301;
	b_ref = 0xefcdab89;
	c_ref = 0x98badcfe;
	d_ref = 0x10325476;

	// 512-bit block to be hashed
	uint8_t block [64] = {0x00};
}
