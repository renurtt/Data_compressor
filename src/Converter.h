//
// Created by Renat Nurtdinov on 30.03.2020.
//
#include <cstdlib>
#include <string>

using namespace std;

#ifndef NURTDINOV_KDZ_COMPRESSOR_CONVERTER_H
#define NURTDINOV_KDZ_COMPRESSOR_CONVERTER_H


struct Converter
{
public:
    static string char2bin(unsigned char code, char len);

    static char bin2char(string bin);

    static unsigned long char2ulong(char *m);

    static string ushort2binstr(unsigned short n, int len);

    static unsigned short binstr2ushort(string str);

    static int binstr2int(string bin);

    static string int2binstr(int n, int len);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_CONVERTER_H