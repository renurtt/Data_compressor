//
// Created by Renat Nurtdinov on 07.04.2020.
//

#ifndef NURTDINOV_KDZ_COMPRESSOR_LZWPACKER_H
#define NURTDINOV_KDZ_COMPRESSOR_LZWPACKER_H

#include <map>
#include <fstream>
#include "Converter.h"

using namespace std;

class LzwPacker
{
public:
    static string pack(const string &original_filename);

private:
    static string read_complete_file(ifstream &input);

    static void write_to_file(ofstream &output, string &str_to_write);

    static void compress_all(map<string, int> dict, int dict_size, string &inp_str, string &res);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_LZWPACKER_H
