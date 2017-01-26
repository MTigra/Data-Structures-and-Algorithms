//
// Created by Nikita Marinosyan on 29.11.16.
//

#include "utilities.h"

map<char, int> getFrequencyMap(string path, unsigned int &length) {

    // Create stream to
    // read from the file
    ifstream input_stream;

    // Create map to
    // store frequencies
    map<char, int> frequencyMap;

    // Open the stream with
    // the defined path
    input_stream.open(path);

    // Calculate frequency of each
    // character met in the file
    char c;
    while (input_stream >> noskipws >> c) {
        frequencyMap[c] += 1;
        ++length;
        operations += 3;
    }

    // Close the stream
    input_stream.close();

    operations += 1;
    // Return frequency info
    return frequencyMap;
}

void compressFile(map<char, string> codes, unsigned int length, string ipath, string opath) {

    // Create input and
    // output streams
    // and open them
    ofstream ostream(opath, ios::binary | ios::out);;
    ifstream istream(ipath);

    // Utility variable to
    // store current character
    char c;

    // Utility variable to store
    // the binary code of
    // current character
    string code;

    // Utility variable to
    // control the size of byte
    int byte_count = 0;

    // Utility variable
    // to imitate byte
    char byte = 0;

    operations += 4;

    // Add coding table
    // at the beginning
    // of the file
    ostream.write((char *) &length, sizeof(unsigned int));
    unsigned char t = (int)codes.size();
    ostream.write((char *) &t, sizeof(unsigned char));
    operations += 3;
    for (map<char, string>::iterator itr = codes.begin(); itr != codes.end(); ++itr) {
        ostream.write((char*) &itr->first, sizeof(char));
        operations += 3;
    }
    operations += 1;
    for (map<char, string>::iterator itr = codes.begin(); itr != codes.end(); ++itr) {
        short l = itr->second.length();
        ostream.write((char *) &l, sizeof(short));
        operations += 3;
    }
    for (map<char, string>::iterator itr = codes.begin(); itr != codes.end(); ++itr) {
        for (int i = 0; i < itr->second.length(); ++i) {

            // Write the next bit of current
            // character bin code to the byte
            byte = byte | (itr->second[i] == '1' ? 1 : 0) << (7 - byte_count);

            // Mark the next bit as filled
            ++byte_count;

            // Check if the byte is full
            if (byte_count == 8) {

                // Write the next byte
                ostream.write(&byte, sizeof(char));

                // Clear byte
                byte = 0;
                byte_count = 0;

                operations += 3;
            }
            operations += 9;
        }
        operations += 2;
    }
    operations += 2;

    // Now we need to write
    // the text itself
    while (!istream.eof()) {

        // Read the next character
        istream >> noskipws >> c;

        // Find the code
        // of the character
        code = codes[c];

        // Write the next byte
        for (int i = 0; i < code.length(); ++i) {

            // Write the next bit of current
            // character bin code to the byte
            byte = byte | (code[i] == '1' ? 1 : 0) << (7-byte_count);

            // Mark the next bit as filled
            ++byte_count;

            // Check if the byte is full
            if (byte_count == 8) {

                // Write the next byte
                ostream.write(&byte, sizeof(char));

                // Clear byte
                byte = 0;
                byte_count = 0;
                operations += 3;
            }
            operations += 9;
        }
        operations += 4;
    }

    // Write the
    // last byte
    if (byte_count != 0) {
        for (int i = 0; i < 8 - byte_count; ++i) {
            byte = byte | 0 << (7 - byte_count);
            operations += 7;
        }
        operations += 1;
    }
    ostream.write(&byte, sizeof(char));

    // Close file streams
    istream.close();
    ostream.close();
    operations += 4;
}

void decompressFile(string ipath, string opath) {

    // Create input and output
    // streams and open them
    ifstream istream(ipath, ios::binary);
    ofstream ostream(opath);

    // Read the number of characters
    // in the initial file
    unsigned int length;
    istream.read((char*)&length, sizeof(unsigned int));

    // Read the number of
    // unique characters in file
    unsigned char tmp;
    istream.read((char*) &tmp, sizeof(unsigned char));
    int uniqueSymbols = tmp;

    operations += 5;

    // Read the unique symbols
    vector<char> chars;
    for (int i = 0; i < uniqueSymbols; ++i) {
        char next_symbol;
        istream.read(&next_symbol, sizeof(char));
        chars.push_back(next_symbol);

        operations += 4;
    }
    operations += 1;

    // Read the lengths of
    // binary codes
    vector<short> lengths;
    for (int j = 0; j < uniqueSymbols; ++j) {
        short t_length;
        istream.read((char*) &t_length, sizeof(short));
        lengths.push_back(t_length);

        operations += 4;
    }

    // Create variables
    // to imitate byte
    char byte = 0;
    int byte_count = 0;

    operations += 4;

    // Read codes of
    // the characters
    vector<string> codes(uniqueSymbols, "");
    for (int k = 0; k < uniqueSymbols; ++k) {
        for (short i = 0; i < lengths[k]; ++i) {
            if (byte_count == 0) {
                istream.read(&byte, sizeof(char));
                operations += 1;
            }

            if(byte & (1 << (7 - byte_count))) {
                codes[k] += "1";
            }
            else {
                codes[k] += "0";
            }

            ++byte_count;
            if (byte_count == 8) {
                byte_count = 0;

                operations += 1;
            }

            operations += 7;
        }
        operations += 3;
    }
    operations += 1;

    // Create codes table
    map<string, char> codesTable;
    for (int l = 0; l < uniqueSymbols; ++l) {
        codesTable[codes[l]] = chars[l];
        operations += 1;
    }
    operations += 1;

    // Read the main characters
    // and write them to the
    // output file
    for (int i = 0; i < length; ++i) {
        string buf = "";
        while (codesTable.count(buf) == 0) {
            if (byte_count == 0) {
                istream.read(&byte, sizeof(char));
                operations += 1;
            }

            if(byte & 1 << (7 - byte_count)) {
                buf += "1";
            }
            else {
                buf += "0";
            }

            ++byte_count;
            if (byte_count == 8) {
                byte_count = 0;
                operations += 1;
            }

            operations += 8;
        }
        ostream.write(&codesTable[buf], sizeof(char));
        operations += 4;
    }
    operations += 1;

    // Close streams
    istream.close();
    ostream.close();
    operations += 2;
}

long operations = 0;