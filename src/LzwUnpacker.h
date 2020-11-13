//
// Created by Renat Nurtdinov on 07.04.2020.
//

#ifndef NURTDINOV_KDZ_COMPRESSOR_LZWUNPACKER_H
#define NURTDINOV_KDZ_COMPRESSOR_LZWUNPACKER_H

#include <map>
#include <fstream>
#include "Converter.h"

class LzwUnpacker
{
public:
    static void unpack(const string &compressed_filename);

private:
    static void read_all_compressed(ifstream &compressed, string &str);

    static void
    decompress_all(string &compressed_str, map<int, string> &dict_i2s, map<string, int> &dict_s2i, int dict_size,
                   string &res);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_LZWUNPACKER_H
