//
// Created by Renat Nurtdinov on 07.04.2020.
//

#include "LzwUnpacker.h"

void LzwUnpacker::read_all_compressed(ifstream &compressed, string &str)
{
    char buff[1];
    while (true)
    {
        compressed.read(buff, 1);
        if (compressed.eof())
            break;
        str += Converter::char2bin(buff[0], 8);
    }
}

void LzwUnpacker::unpack(const string &compressed_filename)
{
    int dict_size = 1024;
    ifstream compressed(compressed_filename, ios::binary);
    fstream decompressed;
    string decompressed_filename = compressed_filename.substr(0, compressed_filename.find('.', 0))
                                   + ".unlzw";
    decompressed.open(decompressed_filename, ios::out);
    string compressed_str;
    read_all_compressed(compressed, compressed_str);

    map<int, string> dict_i2s;
    map<string, int> dict_s2i;
    unsigned char c;
    for (int i = 0; i < 256; ++i)
    {
        c = i;
        dict_i2s[i] = string(1, c);
        dict_s2i[string(1, c)] = i;
    }

    string res;
    decompress_all(compressed_str, dict_i2s, dict_s2i, dict_size, res);

    decompressed << res;
}

void
LzwUnpacker::decompress_all(string &compressed_str, map<int, string> &dict_i2s, map<string, int> &dict_s2i,
                            int dict_size, string &res)
{
    int signs_numb = 8;
    long next_code = 256;
    int signs_numb_pow = 256;

    string x = compressed_str.substr(0, signs_numb);
    int ptr = 8;

    string y;

    string temp;
    while (ptr + signs_numb < compressed_str.size())
    {
        if (next_code > signs_numb_pow - 1)
        {
            signs_numb++;
            signs_numb_pow *= 2;
        }
        y = compressed_str.substr(ptr, signs_numb);
        ptr += signs_numb;

        temp = dict_i2s[Converter::binstr2int(x)] + dict_i2s[Converter::binstr2int(y)][0];
        if (dict_s2i.count(temp) > 0)
            x += y;
        else
        {
            res += dict_i2s[Converter::binstr2int(x)];

            if (next_code - 1 < dict_size)
            {
                dict_i2s[next_code] = temp;
                dict_s2i[temp] = next_code++;
            }
            x = y;
        }
    }
    res += dict_i2s[Converter::binstr2int(x)];
}
