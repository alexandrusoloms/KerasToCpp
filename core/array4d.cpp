////
//// Created by mariussolomes on 19/07/19.
////
//
//#include "../inc/Matrix4D.h"
//
//
//Matrix4D::Matrix4D(int n_rows, int n_cols, int n_depth, int n): rows(n_rows), cols(n_cols), depth(n_depth), depth2(n) {
//    init();
//}
//
//void Matrix4D::init() {
//    data.resize(rows * cols * depth * depth2);
//
//    for (int i=0; i<rows; i++){
//        for (int j=0; j<cols; j++){
//            for (int k=0; k<depth; k++){
//                for (int l=0; l<depth2; l++){
//                    data[i][j][k][l] = 0;
//                }
//            }
//        }
//    }
//}