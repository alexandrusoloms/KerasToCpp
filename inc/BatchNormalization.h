//
// Created by mariussolomes on 26/07/2019.
//

#ifndef KERASTOCPP_BATCHNORMALIZATION_H
#define KERASTOCPP_BATCHNORMALIZATION_H

#include "BaseDataUnit.h"
#include <math.h>

class BatchNormalization{
public:
    BatchNormalization(array4d* input, array4d* gamma, array4d* beta, array4d* mean, array4d* variance);

    array4d forward(bool flattened=false);

    array4d *input, *gamma, *beta, *mean, *variance;
};

BatchNormalization::BatchNormalization(array4d *input, array4d *gamma, array4d *beta, array4d *mean,
                                       array4d *variance): input(input), gamma(gamma), beta(beta), mean(mean), variance(variance) {

}

array4d BatchNormalization::forward(bool flattened) {


    array4d out(input->d1, input->d2, input->d3, input->d4);
    if (!flattened) {
        for (int i = 0; i < input->d1; i++) {
            for (int j = 0; j < input->d2; j++) {
                for (int k = 0; k < input->d3; k++) {
                    for (int l = 0; l < input->d4; l++) {
                        float tmp = gamma->at(l, 0, 0, 0) / sqrtf(variance->at(l, 0, 0, 0) + 0.001f) *
                                    input->at(i, j, k, l);
                        tmp = tmp + (beta->at(l, 0, 0, 0) - (gamma->at(l, 0, 0, 0) * mean->at(l, 0, 0, 0)) /
                                                            sqrtf(variance->at(l, 0, 0, 0) + 0.001f));
                        out.at(i, j, k, l) = tmp;
                    }
                }
            }
        }
    } else {

        for (int i = 0; i < input->d1; i++) {
            for (int j = 0; j < input->d2; j++) {
                for (int k = 0; k < input->d3; k++) {
                    for (int l = 0; l < input->d4; l++) {
                        float tmp = gamma->at(j, 0, 0, 0) / sqrtf(variance->at(j, 0, 0, 0) + 0.001f) *
                                    input->at(i, j, k, l);
                        tmp = tmp + (beta->at(j, 0, 0, 0) - (gamma->at(j, 0, 0, 0) * mean->at(j, 0, 0, 0)) /
                                                            sqrtf(variance->at(j, 0, 0, 0) + 0.001f));
                        out.at(i, j, k, l) = tmp;
                    }
                }
            }
        }

    }

    return out;
}


#endif //KERASTOCPP_BATCHNORMALIZATION_H
