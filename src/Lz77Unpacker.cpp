//
// Created by Renat Nurtdinov on 31.03.2020.
//

#include "Lz77Unpacker.h"

string
Lz77Unpacker::decompress_all(ifstream &compressed, fstream &decompressed, short offset_bits_num, short length_bits_num)
{
    string res = "";
    unsigned short offset = 0, length = 0;
    char symb;
    bool is_symb_filled;
    unsigned long res_s;
    string compressed_str;
    read_all_compressed(compressed, compressed_str);
    int ptr = 0;
    while (ptr + offset_bits_num < compressed_str.size())
    {
        offset = Converter::binstr2ushort(compressed_str.substr(ptr, offset_bits_num));
        ptr += offset_bits_num;
        if (offset != 0)
        {
            length = Converter::binstr2ushort(compressed_str.substr(ptr, length_bits_num)) + 1;
            ptr += length_bits_num;
        } else
            length = 0;

        is_symb_filled = false;
        if (ptr + 8 < compressed_str.size())
        {
            symb = Converter::bin2char(compressed_str.substr(ptr, 8));
            is_symb_filled = true;
            ptr += 8;
        }

        res_s = res.size();
        string s = res.substr(res_s - offset, offset);
        while (length > offset)
        {
            res += s;
            length -= offset;
        }

        res += res.substr(res_s - offset, length);

        if (is_symb_filled)
            res += symb;
    }
    return res;
}

void Lz77Unpacker::read_all_compressed(ifstream &compressed, string &str)
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

string Lz77Unpacker::unpack(const string &compressed_filename)
{
    ifstream compressed(compressed_filename, ios::binary);
    int sliding_window_size_kb = stoi(compressed_filename.substr(compressed_filename.find('.', 0) + 5));
    int background_size_kb = 0.8 * sliding_window_size_kb;

    string decompressed_filename = compressed_filename.substr(0, compressed_filename.find('.', 0))
                                   + ".unlz77" + to_string(sliding_window_size_kb);
    fstream decompressed;
    decompressed.open(decompressed_filename, ios::out);

    short offset_bits_num = ceil(log2(background_size_kb * 1024)) + 1;
    short length_bits_num = ceil(log2((sliding_window_size_kb - background_size_kb) * 1024));
    string res = decompress_all(compressed, decompressed, offset_bits_num, length_bits_num);

    decompressed << res;

    compressed.close();
    decompressed.close();
    return decompressed_filename;
}