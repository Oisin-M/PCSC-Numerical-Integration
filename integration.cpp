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
    Eigen::VectorXcd vec(2);
    vec(0)= std::complex<double>(2*x+y, 2*x-y);
    vec(1)= std::complex<double>(-2*x-y, -y);
    return vec;
}

int main() {

    Eigen::MatrixX2d boundsX(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps(2,2); //X rows, 2 columns and ints
    for (int i=0; i<2; i++) {
        boundsX(0,i)=i+1;
        boundsY(0,i)=i+1;
        noSteps(0,i)=i+1;
    }
    for (int i=0; i<2; i++) {
        boundsX(1,i)=i+1;
        boundsY(1,i)=i+1;
        noSteps(1,i)=i+1;
    }
    int D=2;
    int m=2;
    Data input = { .boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .f = &func, .D=D, .m=m};

    TrapezoidalRule solver = TrapezoidalRule(input);
    std::cout << solver.Solve();

    //We need to delete pointer after but this doesn't work...
    //delete input.f;

    return 0;
}