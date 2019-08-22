//
// Created by mariussolomes on 19/07/19.
//

#ifndef KERASTOCPP_SIGMOID_H
#define KERASTOCPP_SIGMOID_H

#include <math.h>
#include "array4d.h"

float sigmoid(float x){
    return 1 / (1 + exp(- x));
}

Matrix<float> sigmoidMatrix(Matrix<float>* m){
    for (int i=0; i<m->rows*m->cols; i++){
        m->data[i] = sigmoid(m->data[i]);
    }
    return *m;
}

array4d sigmoid(array4d *in){
    array4d out(in->d1, in->d2, in->d3, in->d4);

    for (int i=0; i<in->d1; i++){
        for (int j=0; j<in->d2; j++){
            for (int k=0; k<in->d3; k++){
                for (int l=0; l<in->d4; l++){
                    out.at(i, j, k, l) = sigmoid(in->at(i, j, k, l));
                }
            }
        }
    }

    return out;
}

#endif //KERASTOCPP_SIGMOID_H
