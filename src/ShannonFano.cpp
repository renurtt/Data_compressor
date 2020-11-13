//
// Created by Renat Nurtdinov on 30.03.2020.
//

#include "ShannonFano.h"

int ShannonFano::findMedian(int h, int l)
{
    int sum_end = 0, sum_begin = 0, previous_diff = 0, curr_diff = 0;
    int med = 0, i, j;

    for (int i = h; i >= l + 1; i--)
        sum_end += alphabet[i].r;
    sum_begin = alphabet[l].r;

    previous_diff = abs(sum_begin - sum_end);
    j = 2;
    while (j != h - l + 1)
    {
        med = l + j;

        sum_begin += alphabet[med - 1].r;

        sum_end -= alphabet[med - 1].r;

        curr_diff = abs(sum_begin - sum_end);

        //if difference increased then the previously found median was right
        if (curr_diff >= previous_diff)
            break;
        previous_diff = curr_diff;
        j++;
    }
    return med - 1;
}

void ShannonFano::algorithm(int l, int h)
{
    int i = 0, d = 0, j = 0, med;
    if ((l + 1) == h || l == h || l > h)
    {
        if (l >= h)
            return;
        alphabet[h].s += "1";
        alphabet[l].s += "0";
        return;
    } else
    {
        med = findMedian(h, l);

        for (i = l; i < med; i++)
            alphabet[i].s += "0";
        for (i = med; i <= h; i++)
            alphabet[i].s += "1";

        // Invoke shannon function
        algorithm(l, med - 1);
        algorithm(med, h);
    }
}

void ShannonFano::build()
{
    algorithm(0, alphabet.size() - 1);
}

void ShannonFano::addChance(int repitations)
{
    alphabet.emplace_back(repitations);
}

string ShannonFano::get(int i)
{
    return alphabet[i].s;
}