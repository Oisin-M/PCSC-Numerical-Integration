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
    Eigen::VectorXcd (*f)(double x, double y); //pointer to function which returns complex vector
    int D;
    int m;
};

#endif //DATASTRUCT_H
