//
// Created by mariussolomes on 18/07/19.
//

#ifndef KERASTOCPP_CONVOLUTION2D_H
#define KERASTOCPP_CONVOLUTION2D_H

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include "array4d.h"

using namespace std;

/**
 * CONVOLUTION2D for an image, shape (height x width)
 *
 * array data structure
 */
class Convolution2D{
public:
    Convolution2D(array4d *inputArray, array4d *kernel,
                  array4d *bias);

    array4d forward();
    array4d forward3x1();
    array4d multiplyRegion(array4d *imageRegion);


    array4d* input;
    array4d* filters;
    array4d* bias;

    int track_i;
    int track_j;
};


#endif //KERASTOCPP_CONVOLUTION2D_H
