//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef MIDPOINTFORMULA_H
#define MIDPOINTFORMULA_H

#include "AbstractIntegrationMethod.h"

class MidpointFormula : public AbstractIntegrationMethod {
public:
    MidpointFormula(Data data, Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXd coeff));
    Eigen::VectorXcd Solve();
};

#endif //MIDPOINTFORMULA_H
