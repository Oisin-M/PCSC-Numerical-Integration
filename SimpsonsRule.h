//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef SIMPSONSRULE_H
#define SIMPSONSRULE_H

#include "AbstractIntegrationMethod.h"

/**
* Takes as input a Data struct and implements a Solve() method returning the 2D or 1D Simpson's Rule
* approximation of the integral
* \brief Class implementing the Simpson's Rule approximation of integrals in 2D or 1D
*/
class SimpsonsRule : public AbstractIntegrationMethod {
public:
/** \brief Initialiser setting the data as a Data struct and also the function to integrate
*/
    SimpsonsRule(Data &data, Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXcd &coeff));
/** \brief Method to compute approximate value of the 2D or 1D integral with Simpson's Rule
*/
/**
* Takes as input a Data struct and implements a Solve() method returning the 2D or 1D Simpson's Rule
* approximation of the integral
* \f{eqnarray*}{
I \approx & \frac{h_x h_y}{36} \left[ f(x_0, y_0)+f(x_0,y_f)+f(x_f,y_0)+f(x_f,y_f) \right.\\
& + 4 \left( \sum_{i=1}^{n_y} \left[f(x_0, y_{2i-1})+f(x_f,y_{2i-1})\right] + \sum_{j=1}^{n_x} \left[f(x_{2j-1}, y_0)+f(x_{2j-1},y_f)\right] \right)\\
& + 2 \left( \sum_{i=1}^{n_y-1} \left[f(x_0, y_{2i})+f(x_f,y_{2i})\right] + \sum_{j=1}^{n_x-1} \left[f(x_{2j}, y_0)+f(x_{2j},y_f)\right] \right) \\
& + 4 \left( \sum_{i=1}^{n_y-1} \sum_{j=1}^{n_x-1} f(x_{2j}, y_{2i}) \right) + 16 \left( \sum_{i=1}^{n_y} \sum_{j=1}^{n_x} f(x_{2j-1}, y_{2i-1}) \right) \\
& \left. +8 \left( \sum_{i=1}^{n_y} \sum_{j=1}^{n_x-1} f(x_{2j}, y_{2i-1})  +   \sum_{i=1}^{n_y-1} \sum_{j=1}^{n_x} f(x_{2j-1}, y_{2i}) \right) \right]
\f}
*/
/*!
\return The complex vector result of the integral approximation
*/
    Eigen::VectorXcd Solve();
};

#endif //SIMPSONSRULE_H
