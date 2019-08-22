//
// Created by mariussolomes on 19/07/19.
//

#ifndef KERASTOCPP_ARRAY4D_H
#define KERASTOCPP_ARRAY4D_H

#include <vector>
#include <assert.h>

using namespace std;


struct array4d
{
    array4d(int d1, int d2, int d3, int d4) :
            d1(d1), d2(d2), d3(d3), d4(d4), data(d1*d2*d3*d4) {}

    float& at(int i1, int i2, int i3, int i4)
    {
        return data[getIndex(i1, i2, i3, i4)];
    }

    int getIndex(int i1, int i2, int i3, int i4)
    {
        assert(i1 >= 0 && i1 < d1);
        assert(i2 >= 0 && i2 < d2);
        assert(i3 >= 0 && i3 < d3);
        assert(i4 >= 0 && i4 < d4);

        // ??? Need to verify the formula.
        return (((i1*d2 + i2)*d3 + i3)*d4 + i4);
    }

    int d1;
    int d2;
    int d3;
    int d4;
    std::vector<float> data;
    string name = "";

};

#endif //KERASTOCPP_ARRAY4D_H
