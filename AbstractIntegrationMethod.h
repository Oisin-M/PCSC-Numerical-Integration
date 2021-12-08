//
// Created by morrison@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef ABSTRACTINTEGRATIONMETHOD_H
#define ABSTRACTINTEGRATIONMETHOD_H

#include "DataStruct.h"

class AbstractIntegrationMethod {
public:
    AbstractIntegrationMethod(Data data, Eigen::VectorXcd (*function)(double x, double y, Eigen::MatrixXd coeff));
    
    virtual Eigen::VectorXcd Solve()=0;

protected:
    Data data;
    Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXd coeff);
};

#endif //ABSTRACTINTEGRATIONMETHOD_H
