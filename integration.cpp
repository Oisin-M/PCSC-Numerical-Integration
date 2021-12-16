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

void printResult(Eigen::VectorXcd &result, int m) {
    std::cout << "[ ";
    for (int i=0; i<m-1; i++) {
        std::cout << std::real(result(i)) << " + " << std::imag(result(i)) << "i," << std::endl;
    }
    std::cout << std::real(result(m-1)) << " + " << std::imag(result(m-1)) << "i ]" << std::endl << std::endl;;
}

int main() {
    std::string filename = "../readfile.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    std::cout << std::endl;

    std::cout << "---Input Data---" << std::endl << std::endl;
    std::cout << "D: " << data.D << std::endl;
    std::cout << "m: " << data.m << std::endl;
    std::cout << "boundsX: " << std::endl << data.boundsX << std::endl;
    std::cout << "boundsY: " << std::endl << data.boundsY << std::endl;
    std::cout << "noSteps: " << std::endl << data.noSteps << std::endl;
    std::cout << "coefficients: " << std::endl << data.coefficients << std::endl << std::endl;

    std::cout << "---Integration Methods---" <<std::endl << std::endl;
    std::cout << "MidpointFormula:" << std::endl;

    MidpointFormula midpt = MidpointFormula(data, &func);
    Eigen::VectorXcd result_mid = midpt.Solve();
    printResult(result_mid, data.m);

    std::cout << "TrapezoidalRule:" << std::endl;

    TrapezoidalRule trapz = TrapezoidalRule(data, &func);
    Eigen::VectorXcd result_trapz = trapz.Solve();
    printResult(result_trapz, data.m);

    std::cout << "SimpsonsRule:" << std::endl;

    SimpsonsRule simps = SimpsonsRule(data, &func);
    Eigen::VectorXcd result_simps = simps.Solve();
    printResult(result_simps, data.m);

    return 0;
}