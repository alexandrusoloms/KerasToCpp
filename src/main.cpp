#include "../inc/matrix.h"
#include "../inc/read.h"
#include "../inc/Convolution2D.h"
#include "../inc/MaxPooling.h"
#include "../inc/sigmoid.h"
#include "../inc/leakyReLu.h"
#include "../inc/BatchNormalization.h"
#include "../inc/array4d.h"


struct Dense{
    Dense(array4d* input, array4d* weights, array4d* bias):
          input(input), weights(weights), bias(bias){};

    array4d forward(){
        Matrix inputMatrix(input->d1, input->d2);
        inputMatrix.data = input->data;

        Matrix weightsMatrix(weights->d1, weights->d2);
        weightsMatrix.data = weights->data;

        Matrix biasMatrix(bias->d1, bias->d2);
        biasMatrix.data = bias->data;

        Matrix postMult = matrixDotProduct(&inputMatrix, &weightsMatrix);
        Matrix output= matrixAddition(&postMult, &biasMatrix);

        array4d out(output.rows, output.cols, 1, 1);
        out.data = output.data;
        return out;

    }

    array4d* input;
    array4d* weights;
    array4d* bias;
};

int main(int argc, char* argv[]) {

    /**
     * reading input
     */
    std::string fname(argv[1]);
    array<array<float, 80>, 998> a = readFromFile(fname);
    array4d input(1, 998, 80, 1);

    int counter = 0;
    for (int i = 0; i < 998; i++) {
        for (int j = 0; j < 80; j++) {
            input.data[counter] = a[i][j];
//            cout << input.data[counter] << endl;
            counter++;
        }
    }

    /**
     * reading model params
     */
     // "/home/mariussolomes/final_project/summer2019/repos/KerasToCpp/data/final_model5.txt"
    vector<array4d> dataChunks = readModel("/homes/amsolomes1/KerasToCpp/data/final_model9.txt");
    
    bool flat = false;
    int maxPoolCounter = 0;
    for (auto itr = dataChunks.begin(); itr != dataChunks.end(); itr++) {
//        cout << itr->name << endl;

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

        else if (itr->name == "MaxPooling2D"){
            MaxPooling m(&input);
            if (maxPoolCounter == 2){
                input = m.forward3x1();
            }
            else {
                input = m.forward();
                maxPoolCounter++;
            }
            float t=0;
        }

        else if (itr->name == "sigmoid"){
            input = sigmoid(&input);
            float t=0;
        }

        else if (itr->name == "BatchNormalization"){
            array4d gamma = *itr;
            array4d beta = *(itr + 1);
            array4d mean = *(itr + 2);
            array4d variance = *(itr + 3);
            BatchNormalization BN(&input, &gamma, &beta, &mean, &variance);
            input = BN.forward(flat);
            itr = (itr + 3);
        }

        else if (itr->name == "LeakyReLU"){
            input = leakyReLu(&input);
            float t=0;
        }

        else if (itr->name == "Flatten"){
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
            flat = true;
            float t=0;
        }

        else if (itr->name == "Dense") {
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