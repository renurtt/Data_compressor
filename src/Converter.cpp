//
// Created by Renat Nurtdinov on 30.03.2020.
//

#include "Converter.h"

string Converter::char2bin(unsigned char code, char len)
{
    string str_code;
    do
    {
        str_code = string(1, '0' + (code % 2)) + str_code;
        code = code / 2;
    } while (code > 0);

    str_code = string(len - str_code.size(), '0') + str_code;
    return str_code;
}

char Converter::bin2char(string bin)
{
    char code_char = 0;
    for (int j = 0; j <= bin.size() - 1; ++j)
    {
        bin[j] == '0' ? (code_char *= 2) : (code_char = code_char * 2 + 1);
    }
    return code_char;
}

unsigned long Converter::char2ulong(char *m)
{
    string s;
    unsigned long res = 0;
    for (int i = 3; i >= 0; --i)
    {
        s = char2bin(m[i], 8);
        for (int j = 0; j < 8; ++j)
        {
            s[j] == '0' ? (res *= 2) : (res = res * 2 + 1);
        }
    }
    return res;
}

string Converter::ushort2binstr(unsigned short n, int len)
{
    string str;
    do
    {
        str = string(1, '0' + (n % 2)) + str;
        n = n / 2;
    } while (n > 0);
    str = string(len - str.size(), '0') + str;
    return str;
}

unsigned short Converter::binstr2ushort(string bin)
{
    unsigned short n = 0;

    for (int j = 0; j <= bin.size() - 1; ++j)
    {
        bin[j] == '0' ? (n *= 2) : (n = n * 2 + 1);
    }

    return n;
}

int Converter::binstr2int(string bin)
{
    int n = 0;

    for (int j = 0; j <= bin.size() - 1; ++j)
    {
        bin[j] == '0' ? (n *= 2) : (n = n * 2 + 1);
    }
    return n;
}

string Converter::int2binstr(int n, int len)
{
    string str;
    do
    {
        str = string(1, '0' + (n % 2)) + str;
        n = n / 2;
    } while (n > 0);
    str = string(len - str.size(), '0') + str;
    return str;
}