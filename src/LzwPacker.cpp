//
// Created by Renat Nurtdinov on 07.04.2020.
//

#include "LzwPacker.h"

string LzwPacker::pack(const string &original_filename)
{
    int dict_size = 1024;
    ifstream input(original_filename, ios::binary);
    string compressed_filename = original_filename.substr(0, original_filename.find('.', 0))
                                 + ".lzw";
    ofstream output(compressed_filename, ios::out | ios::binary);

    map<string, int> dict;

    string inp_str = read_complete_file(input);

    unsigned char c;
    for (int i = 0; i < 256; ++i)
    {
        c = i;
        dict[string(1, c)] = i;
    }

    string res;
    compress_all(dict, dict_size, inp_str, res);

    write_to_file(output, res);

    return compressed_filename;
}

string LzwPacker::read_complete_file(ifstream &input)
{
    string inp_str = "";
    char buff[1];

    while (true)
    {
        input.read(buff, 1);
        if (input.eof())
            break;
        inp_str += buff[0];
    }
    return inp_str;
}

void LzwPacker::write_to_file(ofstream &output, string &str_to_write)
{
    unsigned long ptr = 0;
    char temp;
    int numb_of_zeros = 8 - (str_to_write.size() % 8);
    if (numb_of_zeros == 8)
        numb_of_zeros = 0;
    str_to_write += string(numb_of_zeros, '0');

    while (ptr < str_to_write.size())
    {
        temp = Converter::bin2char(str_to_write.substr(ptr, 8));
        output.write((char *) &temp, 1);
        ptr += 8;
    }
}

void LzwPacker::compress_all(map<string, int> dict, int dict_size, string &inp_str, string &res)
{
    int signs_numb = 8;
    long signs_numb_pow = 256;
    int next_code = 256;
    unsigned long ptr = 0;
    string x;
    x += inp_str[ptr++];
    char y;
    while (ptr < inp_str.size())
    {
        y = inp_str[ptr++];
        if (dict.count(x + y) > 0)
            x += y;
        else
        {
            res += Converter::int2binstr(dict[x], signs_numb);
            if (next_code - 1 < dict_size)
            {
                if (next_code > signs_numb_pow - 1)
                {
                    signs_numb++;
                    signs_numb_pow *= 2;
                }
                dict[x + y] = next_code++;
            }
            x = y;
        }
    }
    res += Converter::int2binstr(dict[x], signs_numb);
}
