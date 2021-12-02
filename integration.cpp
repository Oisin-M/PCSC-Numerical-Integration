//
// Created by majoor@INTRANET.EPFL.CH on 29.11.21.
//

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <array>
#include <iostream>
#include <memory>

#include "AbstractIntegrationMethod.h"
#include "TrapezoidalRule.h"
#include "DataStruct.h"

Eigen::VectorXcd func(double x, double y) {
    Eigen::VectorXcd vec(1);
    vec(0)= std::complex<double>(2*x+y, 2*x-y);
    return vec;
}

int main() {

    Eigen::MatrixX2d boundsX(1,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY(1,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps(1,2); //X rows, 2 columns and ints
    for (int i=0; i<2; i++) {
        boundsX(0,i)=i+1;
        boundsY(0,i)=i+1;
        noSteps(0,i)=i+1;
    }
    Data input = { .boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .f = &func };

    TrapezoidalRule solver = TrapezoidalRule(input);
    std::cout << solver.Solve();

    //We need to delete pointer after but this doesn't work...
    //delete input.f;

    return 0;
}