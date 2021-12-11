//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef MIDPOINTFORMULA_H
#define MIDPOINTFORMULA_H

#include "AbstractIntegrationMethod.h"

/**
* Takes as input a Data struct and implements a Solve() method returning the Midpoint Formula
* approximation of the integral
* \f$(x_1,y_1)\f$
* \brief Class implementing the Midpoint Formula approximation of integrals
*/

class MidpointFormula : public AbstractIntegrationMethod {
public:
    MidpointFormula(Data data, Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXcd coeff));
    Eigen::VectorXcd Solve();
};

#endif //MIDPOINTFORMULA_H
