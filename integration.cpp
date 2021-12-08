//
// Created by majoor@INTRANET.EPFL.CH on 29.11.21.
//

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <array>
#include <iostream>
#include <memory>

#include "AbstractReader.h"
#include "TxtReader.h"

#include "AbstractIntegrationMethod.h"
#include "MidpointFormula.h"
//#include "TrapezoidalRule.h"
//#include "SimpsonsRule.h"
#include "DataStruct.h"

Eigen::VectorXcd func(double x, double y, Eigen::MatrixXd coeff) {

    int r = coeff.rows();
    int c = coeff.cols();

    Eigen::VectorXcd vec(2);
    vec(0)= std::complex<double>(coeff(0,0)*x+y, coeff(0,0)*x-y);
    vec(1)= std::complex<double>(-coeff(0,0)*x-y, -coeff(0,0)*y);
    return vec;
}


int main() {
    std::string filename = "test.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();

    std::cout << "---Input Data---" << std::endl;
    std::cout << "D: " << data.D << std::endl;
    std::cout << "m: " << data.m << std::endl;
    std::cout << "boundsX: " << std::endl << data.boundsX << std::endl;
    std::cout << "boundsY: " << std::endl << data.boundsY << std::endl;
    std::cout << "noSteps: " << std::endl << data.noSteps << std::endl << std::endl;

    std::cout << "---Integration Methods---" <<std::endl;
    std::cout << "MidpointFormula:" << std::endl;

    MidpointFormula midpt = MidpointFormula(data, &func);
    std::cout << midpt.Solve() << std::endl;

//    std::cout << "TrapezoidalRule:" << std::endl;
//
//    TrapezoidalRule trapz = TrapezoidalRule(data, &func);
//    std::cout << trapz.Solve() << std::endl;
//
//    std::cout << "SimpsonsRule:" << std::endl;
//
//    SimpsonsRule simps = SimpsonsRule(data, &func);
//    std::cout << simps.Solve() << std::endl;

    return 0;
}