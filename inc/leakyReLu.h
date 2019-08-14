//
// Created by mariussolomes on 26/07/2019.
//

#ifndef KERASTOCPP_LEAKYRELU_H
#define KERASTOCPP_LEAKYRELU_H

#include "BaseDataUnit.h"
#include <cmath>

float leakyReLu(float num, float alpha=0.001){
    return max(num, num*alpha);
}

array4d leakyReLu(array4d *in){
    array4d out(in->d1, in->d2, in->d3, in->d4);

    for (int i=0; i<in->d1; i++){
        for (int j=0; j<in->d2; j++){
            for (int k=0; k<in->d3; k++){
                for (int l=0; l<in->d4; l++){
                    out.at(i, j, k, l) = leakyReLu(in->at(i, j, k, l));
                }
            }
        }
    }
    return out;
}

#endif //KERASTOCPP_LEAKYRELU_H
