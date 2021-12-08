//
// Created by morrison@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractIntegrationMethod.h"
#include "DataStruct.h"

AbstractIntegrationMethod::AbstractIntegrationMethod(Data input, Eigen::VectorXcd (*function)(double x, double y, Eigen::MatrixXcd coeff)) {
    data=input;
    f=function;
}