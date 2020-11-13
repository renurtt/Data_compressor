//
// Created by Renat Nurtdinov on 30.03.2020.
//

#include "ShannonUnpacker.h"

string ShannonUnpacker::unpack(const string &compressed_filename)
{
    ifstream compressed(compressed_filename, ios::binary);
    string decompressed_filename = compressed_filename.substr(0, compressed_filename.find('.', 0))
                                   + ".unshan";
    fstream decompressed;
    decompressed.open(decompressed_filename, ios::out);


    char buffer[4];
    compressed.read(buffer, 4);
    unsigned long symbs_number = Converter::char2ulong(buffer);

    //read dictionary
    map<string, char> dictionary = read_dictionary(compressed);


    //read compressed, uncode it and write to decompressed stream byte-by-byte
    decompress_all(compressed, decompressed, dictionary, symbs_number);
    compressed.close();
    decompressed.close();
    return decompressed_filename;
}

map<string, char> ShannonUnpacker::read_dictionary(ifstream &compressed)
{
    map<string, char> dict_unpack;
    char buffer[1];

    compressed.read(buffer, 1);
    char prev_symb, symb = buffer[0], len;
    unsigned char code1;
    string str_code, str_temp_code;
    bool is_first_it = true;
    int iteration_len;
    // continue reading dictionary until we meet two same symbols in a row (as all symbols in dict are to be unique)
    while (prev_symb != symb || is_first_it)
    {
        is_first_it = false;

        compressed.read(buffer, 1);
        len = buffer[0];

        str_code = "";
        for (int j = 0; j < (len - 1) / 8 + 1; ++j)
        {
            compressed.read(buffer, 1);
            code1 = (unsigned char) buffer[0];
            iteration_len = (j == 0) ? (len % 8) : 8;
            iteration_len = (iteration_len == 0) ? 8 : iteration_len;
            str_temp_code = Converter::char2bin(code1, iteration_len);
            str_code += str_temp_code;
        }

        dict_unpack[str_code] = symb;

        compressed.read(buffer, 1);

        prev_symb = symb;
        symb = buffer[0];
    }
    return dict_unpack;
}

void ShannonUnpacker::decompress_all(ifstream &compressed, fstream &decompressed, map<string, char> dictionary,
                                     unsigned long symbs_number)
{
    string temp = "";
    string buffer = "";
    char buff[1];
    int ptr = 1;

    //counter of already read symbols
    unsigned long read_symbs_count = 0;

    while (!compressed.eof() && read_symbs_count < symbs_number)
    {
        //if we reached the end of the buffer and still haven't find such code in dict, than we have to read next byte
        if (ptr == buffer.size() || buffer == "")
        {
            compressed.read(buff, 1);
            if (compressed.eof())
                break;
            buffer += Converter::char2bin(buff[0], 8);
        }
        //taking next char to consideration
        temp = buffer.substr(0, ptr++);
        if (dictionary.count(temp) > 0)
        {
            ++read_symbs_count;
            decompressed << dictionary[temp];
            //"forget" just decoded part of buffer and leave the rest part
            buffer = buffer.substr(ptr - 1, buffer.size() - ptr + 1);
            ptr = 1;
        }
    }
}