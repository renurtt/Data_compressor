//
// Created by Renat Nurtdinov on 31.03.2020.
//

#include "Lz77Packer.h"

string Lz77Packer::pack(const string &original_filename, int sliding_window_size_kb)
{
    ifstream input(original_filename, ios::binary);

    string compressed_filename = original_filename.substr(0, original_filename.find('.', 0))
                                 + ".lz77" + to_string(sliding_window_size_kb);
    ofstream output(compressed_filename, ios::out | ios::binary);

    int background_size_kb = sliding_window_size_kb * 0.8;
    int background_max_size = background_size_kb * 1024;
    int preview_max_size = (sliding_window_size_kb - background_size_kb) * 1024;

    string inp_str = read_complete_file(input);

    compress_all(inp_str, output, background_max_size, preview_max_size);

    input.close();
    output.close();
    return compressed_filename;
}

string Lz77Packer::read_complete_file(ifstream &input)
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

void Lz77Packer::compress_all(string inp_str, ofstream &output, int background_max_size, int preview_max_size)
{
    int background_begin = 0;
    int preview_begin = 0;
    string str_to_write = "";
    short offset_bits_num = ceil(log2(background_max_size)) + 1;
    short length_bits_num = ceil(log2(preview_max_size));

    int preview_rbound, indexof1, indexof2;
    unsigned short length, offset;
    char symb;
    bool is_symb_filled;
    string s;
    while (preview_begin != inp_str.size())
    {
        preview_rbound = min(preview_begin + preview_max_size, (int) inp_str.size()) - 1;

        indexof1 = preview_begin;
        length = 0;
        for (int j = preview_begin; j <= preview_rbound; ++j)
        {
            s = inp_str.substr(preview_begin, j - preview_begin + 1);
            indexof2 = inp_str.find(inp_str.substr(preview_begin, j - preview_begin + 1), background_begin);

            if (indexof2 == string::npos || indexof2 >= preview_begin || length + 2 > preview_max_size)
                break;

            indexof1 = indexof2;
            ++length;
        }

        offset = preview_begin - indexof1;

        if (preview_begin + length < inp_str.size())
        {
            symb = inp_str[preview_begin + length];
            is_symb_filled = true;
        } else
            is_symb_filled = false;

        if (offset == 0)
            add_to_result(output, "0", offset_bits_num,
                          "0", symb, is_symb_filled, str_to_write);
        else
            add_to_result(output, Converter::ushort2binstr(offset, offset_bits_num), offset_bits_num,
                          Converter::ushort2binstr(length - 1, length_bits_num), symb, is_symb_filled, str_to_write);

        preview_begin += (is_symb_filled) ? length + 1 : length;
        background_begin = max(0, preview_begin - background_max_size);
    }
    write_to_file(output, str_to_write);
}

void Lz77Packer::add_to_result(ofstream &output, string offset, int offset_bits_num, string length, char symb,
                               bool is_symb_filled, string &str_to_write)
{
    if (offset == "0")
        str_to_write += string(offset_bits_num, '0');
    else
        str_to_write += offset + length;

    str_to_write += (is_symb_filled) ? Converter::char2bin(symb, 8) : "";
}


void Lz77Packer::write_to_file(ofstream &output, string &str_to_write)
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