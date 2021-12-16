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
#include "TrapezoidalRule.h"
#include "SimpsonsRule.h"
#include "DataStruct.h"

Eigen::VectorXcd func(double x, double y, Eigen::MatrixXcd &coeff) {
    int r = coeff.rows();
    int c = coeff.cols();

    Eigen::VectorXd XandY (c);
    XandY(0) = 1;
    for (int i = 0; i < c - 1; i++){
        int power = ceil((i + 0.5) / 2); // gives 1, 1, 2, 2, 3, 3, ...
        if (i % 2 == 0){
            XandY(i + 1) = pow(x, power);
        }
        else {
            XandY(i + 1) = pow(y, power);
        }
    }
    Eigen::VectorXcd output (r);
    output = coeff * XandY;
    return output;
}


int main() {
    std::string filename = "../readfile.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();

    std::cout << "---Input Data---" << std::endl;
    std::cout << "D: " << data.D << std::endl;
    std::cout << "m: " << data.m << std::endl;
    std::cout << "boundsX: " << std::endl << data.boundsX << std::endl;
    std::cout << "boundsY: " << std::endl << data.boundsY << std::endl;
    std::cout << "noSteps: " << std::endl << data.noSteps << std::endl;
    std::cout << "coefficients: " << std::endl << data.coefficients << std::endl << std::endl;

    std::cout << "---Integration Methods---" <<std::endl << std::endl;
    std::cout << "MidpointFormula:" << std::endl;

    MidpointFormula midpt = MidpointFormula(data, &func);
    auto result_mid = midpt.Solve();
    std::cout << std::real(result_mid(0)) << " + " << std::imag(result_mid(0)) << "i" << std::endl;
    std::cout << std::real(result_mid(1)) << " + " << std::imag(result_mid(1)) << "i" << std::endl << std::endl;

    std::cout << "TrapezoidalRule:" << std::endl;

    TrapezoidalRule trapz = TrapezoidalRule(data, &func);
    auto result_trapz = trapz.Solve();
    std::cout << std::real(result_trapz(0)) << " + " << std::imag(result_trapz(0)) << "i" << std::endl;
    std::cout << std::real(result_trapz(1)) << " + " << std::imag(result_trapz(1)) << "i" << std::endl << std::endl;

    std::cout << "SimpsonsRule:" << std::endl;

    SimpsonsRule simps = SimpsonsRule(data, &func);
    auto result_simps = simps.Solve();
    std::cout << std::real(result_simps(0)) << " + " << std::imag(result_simps(0)) << "i" << std::endl;
    std::cout << std::real(result_simps(1)) << " + " << std::imag(result_simps(1)) << "i" << std::endl;

    return 0;
}