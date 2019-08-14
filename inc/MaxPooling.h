//
// Created by mariussolomes on 18/07/19.
//

#ifndef KERASTOCPP_MAXPOOLING_H
#define KERASTOCPP_MAXPOOLING_H

#include "../inc/Matrix4D.h"
using namespace std;

class MaxPooling{
public:
    MaxPooling(array4d *image);

    array4d forward(bool is3x1=false);
    array4d forward3x1();

private:
    static array4d max(array4d *in);
    static float findMax(array4d *in);

    array4d* input;
};

#endif //KERASTOCPP_MAXPOOLING_H
