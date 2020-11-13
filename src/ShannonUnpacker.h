//
// Created by Renat Nurtdinov on 30.03.2020.
//
#include <fstream>
#include <map>
#include "Converter.h"

using namespace std;
#ifndef NURTDINOV_KDZ_COMPRESSOR_SHANNONUNPACKER_H
#define NURTDINOV_KDZ_COMPRESSOR_SHANNONUNPACKER_H


struct ShannonUnpacker
{
public:
    static string unpack(const string &compressed_filename);

private:
    static map<string, char> read_dictionary(ifstream &compressed);

    static void decompress_all(ifstream &compressed, fstream &decompressed,
                               map<string, char> dictionary, unsigned long symbs_number);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_SHANNONUNPACKER_H
