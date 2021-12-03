//
// Created by majoor@INTRANET.EPFL.CH on 29.11.21.
//

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <array>
#include <iostream>
#include <memory>

#include "AbstractIntegrationMethod.h"
#include "MidpointFormula.h"
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
    std::cout << "---Input Data---" << std::endl;
    std::cout << "D: " << D << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "boundsX: " << std::endl << boundsX << std::endl;
    std::cout << "boundsY: " << std::endl << boundsY << std::endl;
    std::cout << "noSteps: " << std::endl << noSteps << std::endl << std::endl;

    std::cout << "---Integration Methods---" <<std::endl;
    std::cout << "MidpointFormula:" << std::endl;

    MidpointFormula midpt = MidpointFormula(input);
    std::cout << midpt.Solve() << std::endl;

    std::cout << "TrapezoidalRule:" << std::endl;

    TrapezoidalRule trapz = TrapezoidalRule(input);
    std::cout << trapz.Solve() << std::endl;

    return 0;
}