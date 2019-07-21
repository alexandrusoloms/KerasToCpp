//
// Created by mariussolomes on 18/07/19.
//

#include <iostream>
#include "../inc/MaxPooling.h"

MaxPooling::MaxPooling(array4d *image): input(image) {

}

array4d MaxPooling::forward() {
    array4d out(input->d1, (int)input->d2 / 3, (int)input->d3 / 3, input->d4);

    int counter = 0;

    for (int i=0; i<out.d1; i++){
        for (int j=0; j<out.d2; j++){
            for (int k=0; k<out.d3; k++){

                array4d tmp1(1, 3, 3, 16);
                int count = 0;
                for (int l=0; l<out.d4; l++){
                    // (i*3)+l][(j*3)+m][k]
                    array4d tmp(3, 3, 1, 1);
                    int idx = 0;
                    for (int a=0; a<3; a++){
                        for (int b=0; b<3; b++){
                            tmp.data[idx] = input->at(i, j*3 + a, k*3 + b, l);
                            idx++;
                        }
                    }

                    for (int g=0; g<3; g++){
                        for (int f=0; f<3; f++) {
                            tmp1.data[count] = tmp.at(g, f, 0, 0);
                            count++;
                        }
                    }
                }
                array4d maxValues = max(&tmp1);
                /**
                 * updating out be `maxValues`
                 */
                 for (int maxValIndex=0; maxValIndex<maxValues.d1; maxValIndex++){
                     out.data[counter] = maxValues.data[maxValIndex];
                     counter++;
                 }

            }
        }
    }

    return out;
}

// 1x3x3x16
array4d MaxPooling::max(array4d *in) {
    float maxVal = -99999;
    array4d out(16, 1, 1, 1);

    int idx = 0;
    int count = 0;
    for (int i=0; i<(in->d1 * in->d2 * in->d3 * in->d4 + 1); i++){

        if (count < 9){
            // find the max
            float num = in->data[i];
            if (num > maxVal){
                maxVal = num;
            }
        }

        else {
            // we found the max... now we append it to out and
            // reset
            out.data[idx] = maxVal;
            idx++;

            maxVal = -99999;
            count = 0;
        }

        count++;
    }

    return out;
}

//array<float, 16> MaxPooling::max(array<array<array<float, 3>, 3>, 16> in) {
//    float maxVal = -1000;
//
//    array<float, 16> maxValues = {};
//    for (int i=0; i<16; i++){
//        for (int j=0; j<3; j++){
//            for (int k=0; k<3; k++){
//
//                if (in[i][j][k] > maxVal){
//                    maxVal = in[i][j][k];
//                }
//            }
//        }
//        maxValues[i] = maxVal;
//        maxVal = -1000;
//    }
//    return maxValues;
//}


//array4d MaxPooling::forward() {
//
//    array4d out(input->d1, (int)input->d2 / 3, (int)input->d3 / 3, input->d4);
//    for (int i=0; i<out.d2; i++){
//        for (int j=0; j<out.d3; j++){
//
//            /**
//             * extracting the 16x3x3 image region
//             */
//            array<array<array<float, 3>, 3>, 16> imRegion{};
//            for (int k=0; k<16; k++) {
//
//                /**
//                 * extract the image 3x3 region
//                 */
//                 array<array<float, 3>, 3> subImgRegion{};
//                for (int l = 0; l < 3; l++) {
//                    for (int m = 0; m < 3; m++) {
//                        subImgRegion[l][m] = input[(i*3)+l][(j*3)+m][k];
//                    }
//                }
//                imRegion[k] = subImgRegion;
//            } // now we have 16x3x3 imRegions
//            array<float, 16> maxValues = max(imRegion);
//            out[i][j] = maxValues;
//        }
//    }
//    return out;
//}

//array<float, 16> MaxPooling::max(array<array<array<float, 3>, 3>, 16> in) {
//    float maxVal = -1000;
//
//    array<float, 16> maxValues = {};
//    for (int i=0; i<16; i++){
//        for (int j=0; j<3; j++){
//            for (int k=0; k<3; k++){
//
//                if (in[i][j][k] > maxVal){
//                    maxVal = in[i][j][k];
//                }
//            }
//        }
//        maxValues[i] = maxVal;
//        maxVal = -1000;
//    }
//    return maxValues;
//}

