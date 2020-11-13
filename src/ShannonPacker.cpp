//
// Created by Renat Nurtdinov on 30.03.2020.
//

#include "ShannonPacker.h"

string ShannonPacker::pack(const string &original_filename)
{
    ifstream input(original_filename, ios::binary);
    string compressed_filename = original_filename.substr(0, original_filename.find('.', 0))
                                 + ".shan";
    ofstream output(compressed_filename, ios::out | ios::binary);

    //writing file size to file
    unsigned long k = __fs::filesystem::file_size(__fs::filesystem::current_path() / original_filename);
    output.write((char *) &k, 4);

    ShannonFano *shf = new ShannonFano();
    set<pair<char, int>, Comp> symbols_freq = generate_codes(input, shf);

    //write dictionary
    map<char, string> dictionary = write_dictionary(symbols_freq, shf, output);

    delete shf;
    shf = nullptr;
    input.seekg(0);

    //read input, code it and write to output byte-by-byte
    compress_all(input, output, dictionary);

    output.close();
    input.close();
    return compressed_filename;
}

set<pair<char, int>, Comp> ShannonPacker::count_frequency(const vector<char> &v)
{
    map<char, int> freq;

    for (char k : v)
    {
        if (freq.count(k) > 0)
            freq[k] += 1;
        else
            freq[k] = 1;
    }

    Comp compFunctor = [](pair<char, int> e1, pair<char, int> e2) {
        return e1.second >= e2.second;
    };

    // Declaring a set that will store the pairs using above comparision logic
    set<pair<char, int>, Comp> symbols_freq(
            freq.begin(), freq.end(), compFunctor);
    return symbols_freq;
}

set<pair<char, int>, Comp> ShannonPacker::generate_codes(ifstream &input, ShannonFano *shf)
{
    //read all bytes and put to vector
    vector<char> v(std::istreambuf_iterator<char>(input), {});
    //count frequency of all symbols and put to a set with a frequency-descending order rule
    set<pair<char, int>, Comp> symbols_freq = count_frequency(v);

    //build codes for all bytes
    for (pair<char, int> k : symbols_freq)
    {
        shf->addChance(k.second);
    }
    shf->build();

    return symbols_freq;
}

map<char, string>
ShannonPacker::write_dictionary(const set<pair<char, int>, Comp> &symbols_freq, ShannonFano *shf, ofstream &output)
{
    int i = 0;
    map<char, string> dict;
    char *symb;
    char l;
    unsigned char code_char;
    for (pair<char, int> k : symbols_freq)
    {
        string code = shf->get(i++);
        dict[k.first] = code;

        //write symb
        symb = &k.first;
        output.write(symb, 1);

        //write length
        l = (char) (code.size());
        output.write((char *) (&l), 1);

        //write code
        //add zeros to the beginning
        if (code.size() % 8 != 0)
            code = string(8 - (code.size() % 8), '0') + code;

        for (int i1 = 0; i1 < code.size() / 8; ++i1)
        {
            //code_char - number [0;255], decimal representation of symbol's binary code
            //convert part of symbol's code with a length of 8 (byte) to char
            code_char = Converter::bin2char(code.substr(i1 * 8, 8));
            output.write((char *) &code_char, 1);
        }
    }
    // as all symbols in dictionary have to be unique, we use the last symbol already contained in dict
    // to determine the end of a dict
    output.write(symb, 1);

    return dict;
}

void ShannonPacker::compress_all(ifstream &input, ofstream &output, map<char, string> dict)
{
    string buffer;
    string code;
    char code_char;
    while (true)
    {
        char m[1];
        input.read(m, 1);

        if (input.eof())
            break;

        code = dict[m[0]];

        for (char k : code)
        {
            buffer += k;

            if (buffer.size() == 8)
            {
                code_char = Converter::bin2char(buffer);
                output.write((char *) &code_char, 1);
                buffer = "";
            }
        }
    }
    //appending and writing last byte (if needed)
    if (!buffer.empty())
    {
        while (buffer.size() < 8)
            buffer += "1";

        code_char = Converter::bin2char(buffer);
        output.write((char *) &code_char, 1);
    }
}