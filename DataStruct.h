//
// Created by morrison@INTRANET.EPFL.CH on 29.11.21.
//

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <Eigen/Dense>
#include <Eigen/Sparse>

struct Data {
    Eigen::MatrixX2d boundsX; //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY; //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps; //X rows, 2 columns and ints
    Eigen::MatrixXcd coefficients; //store coefficients of polynomial
    int D;
    int m;
};

#endif //DATASTRUCT_H
