//
// Created by Renat Nurtdinov on 30.03.2020.
//
#include <vector>
#include <string>

using namespace std;

#ifndef NURTDINOV_KDZ_COMPRESSOR_SHANNONFANO_H
#define NURTDINOV_KDZ_COMPRESSOR_SHANNONFANO_H


struct node
{
    node(int rep) : r(rep)
    {}

    int r;
    string s;
};

class ShannonFano
{
    vector<node> alphabet;

public:
    int findMedian(int h, int l);

    void algorithm(int l, int h);

    ShannonFano()
    = default;

    void build();

    void addChance(int repitations);

    string get(int i);
};


#endif //NURTDINOV_KDZ_COMPRESSOR_SHANNONFANO_H