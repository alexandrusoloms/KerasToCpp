//
// Created by mariussolomes on 18/07/19.
//

#ifndef KERASTOCPP_READ_H
#define KERASTOCPP_READ_H

#include <iostream>
#include <string>
#include <fstream>
#include <array>

#include "array4d.h"
using namespace std;


array<array<float, 80>, 998> readFromFile(const std::string &fname){
    array<array<float, 80>, 998> arr{};
    ifstream fin(fname.c_str());
    float tmp_float;

    fin >> tmp_float;
    fin >> tmp_float;
    for (int i=0; i<998; i++){
        for (int j=0; j<80; j++){
            fin >> tmp_float;
            arr[i][j] =  tmp_float;
        }
    }
    return arr;

}

array4d read2DConv(const std::string &fname){

    ifstream fin(fname.c_str());
    int d1, d2, d3, d4;
    fin >> d1 >> d2 >> d3 >> d4;
    array4d arr(d1, d2, d3, d4);

    float tmp_float;
    int counter = 0;
    for (int i=0; i<arr.d1; i++){
        for (int j=0; j<arr.d2; j++){
            for (int k=0; k<arr.d3; k++) {
                for (int l=0; l<arr.d4; l++){
                    fin >> tmp_float;
                    arr.data[counter] = tmp_float;
                    counter++;
                }
            }
        }
    }
    return arr;
}

array4d readBias(const std::string &fname){

    ifstream fin(fname.c_str());
    int d1, d2, d3, d4;
    fin >> d1 >> d2 >> d3 >> d4;
    array4d bias(d1, d2, d3, d4);

    float tmp_float;
    for (int i=0; i<16; i++){
        fin >> tmp_float;
        bias.data[i] = tmp_float;
    }
    return bias;
}

Matrix<float> readDense(const std::string &fname){
    ifstream fin(fname.c_str());
    int dim1, dim2;
    fin >> dim1;
    fin >> dim2;

    Matrix<float> dense(dim1, dim2);
//    dense.data.resize(16318464);

    float tmp_float;
    for (int i=0; i<dim1 * dim2; i++){
        fin >> tmp_float;
        dense.data[i] = tmp_float;
    }
    return dense;
}

Matrix<float> readDense1Bias(const std::string &f_name){
    Matrix<float> bias(256, 1);
    ifstream fin(f_name.c_str());

    float tmp_float;
    for (int i=0; i<256; i++){
        fin >> tmp_float;
        bias.data[i] = tmp_float;
    }
    return bias;
}

struct readName{
    readName(ifstream* fin):
        fin(fin){
        *fin >> unitName;
    }

    ifstream* fin;
    string unitName;
};

struct readData{
    readData(ifstream* fin): fin(fin){
        *fin >> unitName;
    }

    array4d read(){

        int d1, d2, d3, d4;
        *fin >> d1;
        *fin >> d2;
        *fin >> d3;
        *fin >> d4;
        array4d arr(d1, d2, d3, d4);

        float tmp_float;
        int counter = 0;
        for (int i=0; i<arr.d1; i++){
            for (int j=0; j<arr.d2; j++){
                for (int k=0; k<arr.d3; k++) {
                    for (int l=0; l<arr.d4; l++){
                        *fin >> tmp_float;
                        arr.data[counter] = tmp_float;
                        counter++;
                    }
                }
            }
        }
        return arr;
    }

    ifstream* fin;
    string unitName;
};

vector<array4d> readModel(const std::string &fileName){
    ifstream fin(fileName.c_str());
    ifstream* t = &fin;
    /**
     * extracting unit type name
     */
    bool nameRead, sizeRead, dataRead = false;
    int fSize;
    fin >> fSize;
    string typeName;

    /**
     * reading file Name
     */
    vector<array4d> dataChunks{};
    for (int i=0; i<fSize; i++) {
        auto *r = new readData(t);
        t = r->fin;
        typeName = r->unitName;
        array4d a = r->read();
        a.name = r->unitName;
        dataChunks.push_back(a);

        delete r;
    }
    return dataChunks;

//    array4d* test = dataUnit.data;
    std::cout << "yo";



}


#endif //KERASTOCPP_READ_H
