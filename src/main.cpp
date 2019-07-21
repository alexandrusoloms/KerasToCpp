#include <Bela-Matrix.h>
#include "../inc/readSpectrogram.h"
#include "../inc/Convolution2D.h"
#include "../inc/MaxPooling.h"
#include "../inc/sigmoid.h"
#include "../inc/Matrix4D.h"


struct Dense{
    Dense(array4d* input, array4d* weights, array4d* bias):
          input(input), weights(weights), bias(bias){};

    array4d forward(){
        Matrix<float> inputMatrix(input->d1, input->d2);
        inputMatrix.data = input->data;

        Matrix<float> weightsMatrix(weights->d1, weights->d2);
        weightsMatrix.data = weights->data;

        Matrix<float> biasMatrix(bias->d1, bias->d2);
        biasMatrix.data = bias->data;

        Matrix<float> postMult = matrixDotProduct(&inputMatrix, &weightsMatrix);
        Matrix<float> output= matrixAddition(&postMult, &biasMatrix);
//        output = sigmoidMatrix(&output);

        array4d out(output.rows, output.cols, 1, 1);
        out.data = output.data;
        return out;

    }

    array4d* input;
    array4d* weights;
    array4d* bias;
};

int main() {

    /**
     * reading input
     */
    array<array<float, 40>, 998> a = readFromFile("../data/spectrogram.dat");
    array4d input(1, 998, 40, 1);

    int counter = 0;
    for (int i = 0; i < 998; i++) {
        for (int j = 0; j < 40; j++) {
            input.data[counter] = a[i][j];
            counter++;
        }
    }

    /**
     * reading model params
     */
    vector<array4d> dataChunks = readModel("../data/full_model.txt");
    
    bool flat = false;
    for (auto itr = dataChunks.begin(); itr != dataChunks.end(); itr++) {
        cout << itr->name << endl;

        if (itr->name == "Conv2D") {
            /**
             * Convolution + MaxPooling + Activation
             */
            array4d kernel = *itr;
            array4d bias = *++itr;
            Convolution2D conv2(&input, &kernel, &bias);
            input = conv2.forward();

            // skipping the next, which is the bias
            itr = itr++;
        }

        if (itr->name == "MaxPooling2D"){
            MaxPooling m(&input);
            input = m.forward();
        }

        if (itr->name == "sigmoid"){
            input = sigmoid(&input);
        }

        if (itr->name == "Flatten"){
            array4d flatten(1, input.d1 * input.d2 * input.d3 * input.d4, 1, 1);
            counter = 0;
            for (int i = 0; i < input.d1; i++) {
                for (int j = 0; j < input.d2; j++) {
                    for (int k = 0; k < input.d3; k++) {
                        for (int l = 0; l < input.d4; l++) {
                            flatten.data[counter] = input.at(i, j, k, l);
                            counter++;
                        }
                    }
                }
            }
            input = flatten;
        }

        if (itr->name == "Dense") {
            /*
             *
             */
            array4d weights = *itr;
            array4d bias = *++itr;
            Dense dense(&input, &weights, &bias);
            input = dense.forward();
            // skipping the next, which is the bias
            itr = itr++;
            }
        }

    std::cout << input.data[0] << endl;
    return 0;
}