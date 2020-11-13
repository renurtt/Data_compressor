//
// Created by Renat Nurtdinov on 31.03.2020.
//

#include <cmath>
#include <fstream>
#include "Converter.h"

using namespace std;

#ifndef NURTDINOV_KDZ_COMPRESSOR_LZ77UNPACKER_H
#define NURTDINOV_KDZ_COMPRESSOR_LZ77UNPACKER_H


struct Lz77Unpacker
{
public:
    static string unpack(const string &compressed_filename);

private:
    static string decompress_all(ifstream &compressed, fstream &decompressed, short i, short i1);

    static void read_all_compressed(ifstream &compressed, string &str);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_LZ77UNPACKER_H
