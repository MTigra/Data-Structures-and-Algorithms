/**
 * @author Nikita Marinosyan
 * @date 26.04.2017
 * Higher School of Economics,
 * Faculty of Computer Science
 *
 * P.S.: I decided not to create .cpp file
 * as it was pointless because some
 * implementation from the task was already here
 */

#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <fstream>

#include  "hashset.h"
#include  "hashset.cpp"

//using namespace std;

// CRC-32C
class hash_function {

public:
    // Here we need to calculate
    // the crc table for CRC-32C
    hash_function()
    {
        unsigned int polynomial = 0x1EDC6F41; // CRC-32C Polynomial

        // 256 codes
        for(unsigned int i = 0; i <= 0xFF; i++)
        {
            this->_crcTable[i] = reflect(i, 8) << 24;

            // 8 bits
            for(int pos = 0; pos < 8; pos++)
            {
                this->_crcTable[i] = (this->_crcTable[i] << 1)
                                       ^ ((this->_crcTable[i] & (1 << 31)) ? polynomial : 0);
            }

            this->_crcTable[i] = this->reflect(this->_crcTable[i], 32);
        }
    }

    unsigned int operator()(const std::string& s) const
    {
        unsigned int crc = 0xffffffff;

        for (int i = 0; i < s.length();)
        {
            crc = (crc>>8) ^ _crcTable[(crc ^ (s[i++])) & 0xFF];
        }

        return crc^0xffffffff;
    }

private:
    // Reflection is required by the CRC32 standard
    unsigned int reflect(unsigned int reflecting, const char c)
    {
        unsigned int value = 0;

        // Swap bits
        for(int pos = 1; pos < (c + 1); pos++)
        {
            if(reflecting & 1)
            {
                value |= (1 << (c - pos));
            }
            reflecting >>= 1;
        }

        return value;
    }

    // CRC lookup table array
    unsigned int _crcTable[256];
};

class equality {
public:
    equality() {}
    bool  operator()(const std::string& a, const std::string& b)  const 
    {
		return  (a == b);
    }
};


class Dictionary: public HashSet<std::string, hash_function, equality>
{
public:
    Dictionary(const std::string& filename)
    {
        // Create the input stream
        std::ifstream infile(filename);

        // Check if the file
        // was opened successfully
        if (!infile.good())
            throw std::invalid_argument("Unable to read the file");

        // Add words from the file
        // to the dictionary
        std::string word;
        while (infile >> word)
            this->insert(word);
    }
};

#endif
