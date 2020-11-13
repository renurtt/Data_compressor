//
// Created by Renat Nurtdinov on 31.03.2020.
//

#include <cmath>
#include <fstream>
#include "Converter.h"

using namespace std;
#ifndef NURTDINOV_KDZ_COMPRESSOR_LZ77PACKER_H
#define NURTDINOV_KDZ_COMPRESSOR_LZ77PACKER_H


struct Lz77Packer
{
public:
    static string pack(const string &original_filename, int sliding_window_size_kb);

private:
    static string read_complete_file(ifstream &input);

    static void compress_all(string inp_str, ofstream &ofstream, int background_max_size, int preview_max_size);

    static void
    add_to_result(ofstream &output, string offset, int offset_bits_num, string length, char symb, bool is_symb_filled,
                  string &str_to_write);

    static void write_to_file(ofstream &output, string &str_to_write);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_LZ77PACKER_H
