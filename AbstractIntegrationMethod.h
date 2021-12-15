//
// Created by morrison@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef ABSTRACTINTEGRATIONMETHOD_H
#define ABSTRACTINTEGRATIONMETHOD_H

#include "DataStruct.h"

/**
* Takes as input a Data struct and implements a Solve() method returning the approximation of the 2D or 1D integral
* \brief Abstract class for implementation of integration algorithms
*/

class AbstractIntegrationMethod {
public:
    /** \brief Initialiser setting the data as a Data struct and also the function to integrate
    */
    AbstractIntegrationMethod(Data &data, Eigen::VectorXcd (*function)(double x, double y, Eigen::MatrixXcd &coeff));

/** \brief Method to compute approximate value of the 2D or 1D integral
 */
/*!
\return The complex vector result of the integral approximation
*/
    virtual Eigen::VectorXcd Solve()=0;

protected:
    Data data;
    Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXcd &coeff);
};

#endif //ABSTRACTINTEGRATIONMETHOD_H
