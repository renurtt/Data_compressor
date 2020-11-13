//
// Created by Renat Nurtdinov on 30.03.2020.
//
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "ShannonFano.h"
#include "Converter.h"

using namespace std;

#ifndef NURTDINOV_KDZ_COMPRESSOR_SHANNONPACKER_H
#define NURTDINOV_KDZ_COMPRESSOR_SHANNONPACKER_H


typedef function<bool(pair<char, int>, pair<char, int>)> Comp;

struct ShannonPacker
{
public:
    static string pack(const string &original_filename);

private:
    static set<pair<char, int>, Comp> count_frequency(const vector<char> &v);

    static set<pair<char, int>, Comp> generate_codes(ifstream &input, ShannonFano *shf);

    static map<char, string>
    write_dictionary(const set<pair<char, int>, Comp> &symbols_freq, ShannonFano *shf, ofstream &output);

    static void compress_all(ifstream &input, ofstream &output, map<char, string> dict);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_SHANNONPACKER_H
