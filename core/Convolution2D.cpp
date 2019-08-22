////
//// Created by mariussolomes on 18/07/19.
////
#include "../inc/Convolution2D.h"

Convolution2D::Convolution2D(array4d *inputArray, array4d *kernel, array4d *bias): input(inputArray), filters(kernel), bias(bias) {

}

array4d Convolution2D::forward() {

    array4d output(1, input->d2 - 2, input->d3 - 2, bias->d1);
    /**
     * Iterating over the image dimensions
     */
    int counter = 0;
    for (int i=0; i<input->d2 - 2; i++){
        for (int j=0; j<input->d3 - 2; j++){

            /**
             * Extracting the 3x3 image
             */
            array4d imRegion(3, 3, input->d4, 1);
            int indx = 0;
            for (int l = 0; l < 3; l++) {
                for (int m = 0; m < 3; m++) {
                    for (int d=0; d<input->d4; d++) {
                        imRegion.data[indx] = input->at(0, i + l, j + m, d);
                        indx++;
                    }
                }
            } // imRegion extracted

            /**
             * Multiplying with kernel and adding bias
             */
            array4d tmp = multiplyRegion(&imRegion);

            /**
             * moving everything into output.data
             */
            for (int a=0; a<tmp.d1; a++){
                for (int b=0; b<tmp.d2; b++){
                    for (int c=0; c<tmp.d3; c++){
                        for (int d=0; d<tmp.d4; d++){
                            output.data[counter] = tmp.at(a, b, c, d);
                            counter++;
                        }
                    }
                }
            } // moving
        }
    }
    return output;

}


/**
 * Multiplying an image region of dimension 4, with a kernel of dimension 4 and adding a bias with dimension 1.
 * @param imageRegion
 * @return 4 dimensional array
 */
array4d Convolution2D::multiplyRegion(array4d *imageRegion) {
    array4d output(bias->d1, 1, 1, 1);

    /**
     * looping over dimensions
     */
     array4d intermediateOutput(filters->d1, filters->d2, filters->d3, filters->d4);

     int counter = 0;
     for (int i=0; i<filters->d1; i++){
         for (int j=0; j<filters->d2; j++){
             for (int k=0; k<filters->d3; k++){
                 for (int l=0; l<filters->d4; l++) {
                     intermediateOutput.data[counter] = (float)(imageRegion->at(i, j, k, 0) * filters->at(i, j, k, l));
                     counter+=1;
                 }
             }
         }
     }

     /**
      * summing over first 3 axis and adding bias
      */
      for (int l=0; l<filters->d4; l++) {
          float sum = 0;
          for (int i = 0; i < filters->d1; i++) {
              for (int j = 0; j < filters->d2; j++) {
                  for (int k = 0; k < filters->d3; k++) {
                      sum += intermediateOutput.at(i, j, k ,l);
                  }
              }
          }
          output.data[l] = sum + bias->at(l, 0, 0, 0);
      }
    return output;

}
//
//
//Convolution2D::Convolution2D(array<array<float, 40>, 998> inputArray, array<array<array<array<float, 3>, 3>, 1>, 16> kernel,
//                             array<float, 16> bias):
//    input(inputArray), filters(kernel), bias(bias) {
//
//}
//
//array<array<array<float, 16>,38>, 996> Convolution2D::forward() {
//    int height = 998;
//    int width = 40;
//
//    array<array<array<float, 16>,38>, 996> forward{};
//    for (int i=0; i <height - 2; i++){
//        for (int j=0; j<width - 2; j++){
//
//            /**
//             * extract the image 3x3 image region
//             */
//            array<array<float, 3>, 3> im_region = {};
//            for (int l=0; l<3; l++){
//                for (int m=0; m<3 ;m++){
//                    im_region[l][m] = input[i+l][j+m];
//                }
//            } // im_region extracted
//
//            /**
//             * multiplying with kernel + adding bias
//             */
//            array<float, 16> out = multiplyRegion(im_region);
//            forward[i][j] = out;
//        }
//    }
//
//    return forward;
//
//}
//
//array<float, 16> Convolution2D::multiplyRegion(array<array<float, 3>, 3> imageRegion) {
//
//    array<float, 16> out = {};
//    for (int i=0; i<16; i++){
//        /**
//         * looping over all kernels
//         */
//         float sumProd = 0;
//         for (int j=0; j<3; j++){
//             for (int k=0; k<3; k++){
//                 /**
//                  * multiplying by filters and adding bias
//                  */
//                 sumProd += imageRegion[j][k] * filters[i][j][k] + bias[i];
//             }
//         }
//         out[i] = sumProd;
//    }
//    return out;
//}
