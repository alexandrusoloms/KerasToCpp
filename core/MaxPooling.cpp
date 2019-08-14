//
// Created by mariussolomes on 18/07/19.
//

#include <iostream>
#include "../inc/MaxPooling.h"

MaxPooling::MaxPooling(array4d *image): input(image) {

}

array4d MaxPooling::forward(bool is3x1) {

    array4d *outPtr;

    array4d tmpOut(input->d1, (int)input->d2 / 3, (int)input->d3 / 3 == 0? 1 : (int)input->d3 / 3, input->d4);
    outPtr = &tmpOut;

    array4d out(outPtr->d1, outPtr->d2, outPtr->d3, outPtr->d4);

    int counter = 0;

    for (int h=0; h<out.d1; h++){
        for (int i=0; i<out.d2; i++){
            for (int j=0; j<out.d3; j++){
                // tmp
                array4d tmp(1, 3, 3, out.d4);
                int c = 0;
                for (int l=0; l<3; l++){
                    for (int m=0; m<3; m++){
                        array4d subTmp(out.d4, 1, 1, 1);
                        for (int k=0; k<out.d4; k++){

                            subTmp.at(k, 0, 0, 0) = input->at(h, i * 3 + l,
                                                                  (j * 3 + m) < input->d3 ? (j * 3 + m) : j, k);
                        }
                        for (auto x: subTmp.data) {
                            tmp.data[c] = x;
                            c++;
                        }
                    }
                }
                array4d maxValues = max(&tmp);
                for (int f=0; f<maxValues.d1 * maxValues.d2 * maxValues.d3 * maxValues.d4; f++){
                    out.data[counter] = maxValues.data[f];
                    counter++;
                }

            }
        }
    }

    return out;
}

// 1x3x3x16
array4d MaxPooling::max(array4d *in) {
    array4d out(in->d4, 1, 1, 1);
    int c=0;
    for (int h=0; h<in->d1; h++){
        for (int k=0; k<in->d4; k++){
            array4d tmp(3, 3, 1, 1);
            int counter = 0;
            for (int i=0; i<3; i++){
                for (int j=0; j<3; j++){
                    tmp.data[counter] = in->at(h, i, j, k);
                    counter++;
                }
            }
            /**
             * finding max
             */
             out.data[c] = findMax(&tmp);
             c++;
        }
    }

    return out;
}

float MaxPooling::findMax(array4d *in) {

    float maxValue = -99999;
    for (int i=0; i<in->d1 * in->d2 * in->d3 * in->d4; i++){
        if (in->data[i] > maxValue){
            maxValue = in->data[i];
        }
    }
    return maxValue;
}

array4d MaxPooling::forward3x1() {
    array4d *outPtr;

    array4d tmpOut(input->d1, (int)input->d2 / 3, input->d3, input->d4);
    outPtr = &tmpOut;
    array4d out(outPtr->d1, outPtr->d2, outPtr->d3, outPtr->d4);

    int counter = 0;

    for (int h=0; h<out.d1; h++){
        for (int i=0; i<out.d2; i++){
            for (int j=0; j<out.d3; j++){
                // tmp
                array4d tmp(1, 3, 3, out.d4);
                int c = 0;
                for (int l=0; l<3; l++){
                    for (int m=0; m<3; m++){
                        array4d subTmp(out.d4, 1, 1, 1);
                        for (int k=0; k<out.d4; k++){
                            subTmp.at(k, 0, 0, 0) = input->at(h, i * 3 + l,
                                                                  j, k);
                        }
                        for (auto x: subTmp.data) {
                            tmp.data[c] = x;
                            c++;
                        }
                    }
                }
                array4d maxValues = max(&tmp);
                for (int f=0; f<maxValues.d1 * maxValues.d2 * maxValues.d3 * maxValues.d4; f++){
                    out.data[counter] = maxValues.data[f];
                    counter++;
                }

            }
        }
    }

    return out;
}
