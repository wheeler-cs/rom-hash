/**
 * @note Algorithms for calculating the CRC32 values were derived from code found at Wikipedia:
 *       https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks#CRC-32_algorithm
 */

#include "hash.hpp"
#include <iostream>

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
uint32_t* calc_md5_str (const std::string &input)
{
	// A, B, C, D
	uint32_t a_ref, b_ref, c_ref, d_ref;
	a_ref = 0x67452301;
	b_ref = 0xefcdab89;
	c_ref = 0x98badcfe;
	d_ref = 0x10325476;
	
	// Padding steps of algorithm
	std::string message_block = input + (char)0x80;
	while ((message_block.size() % 512) != 448)
	{
		message_block += (char)0x00;
	}
	
	// Append length of original message to end of message block (little endian)
	uint8_t message_size_bytes[8];
	uint64_t message_size = input.size();
	for (unsigned int i = 0; i < 8; i++)
	{
		message_size_bytes[i] = (message_size >> (8 * (7 - i))) & 0xff;
	}
	for (unsigned int i = 0; i < 8; i++)
		message_block += (char)message_size_bytes[i];


	// Debugging
	std::cout << std::hex;
	for (unsigned int i = 0; i < message_block.size(); i++)
	{
		if (!(i % 16))
		{
			std::cout << '\n' << i << ": ";
		}
		std::cout << (uint16_t)message_block[i];
	}
	
	// Process 512-bit chunks of data
	uint32_t round_block [16];
	uint32_t a, b, c, d, f, g;
	a = b = c = d = f = g = 0x00000000;
	for (unsigned int i = 0; i < (message_block.size() / 512); i++)
	{
		// Create block to be hashed this round
		for (unsigned int j = 0; j < 16; j++)
		{
			round_block[j] = message_block[(i * 512) + j];
		}
		
		// Load whatever ref values are
		a = a_ref;
		b = b_ref;
		c = c_ref;
		d = d_ref;
		
		// Actual hashing algorithm
		for (uint32_t j = 0; j < 64; j++)
		{
			if (j < 16)
			{
				f = (b & c) | ((!b) & d);
				g = j;
			}
			else if (j < 32)
			{
				f = (d & b) | ((!d) & c);
				g = ((5 * i) + 1) % 16;
			}
			else if (j < 48)
			{
				f = b ^ c ^ d;
				g = ((3 * i) + 5) % 16;
			}
			else
			{
				f = c ^ (b | (!d));
				g = (7 * i) % 16;
			}
			f = f + a + round_block[j] + MD5_LOOKUP_TABLE[g];
			a = d;
			d = c;
			c = b;
			uint32_t f_lr = (f << MD5_SHIFT_TABLE[g]);
			f_lr |= (f >> (32 - MD5_SHIFT_TABLE[g]));
			b = b + f_lr;
		}
		a_ref += a;
		b_ref += b;
		c_ref += c;
		d_ref += d;
	}
	
	uint32_t digest [4];
	digest[0] = a_ref;
	digest[1] = b_ref;
	digest[2] = c_ref;
	digest[3] = d_ref;
}
