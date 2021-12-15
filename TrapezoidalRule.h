//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef TRAPEZOIDALRULE_H
#define TRAPEZOIDALRULE_H

#include "AbstractIntegrationMethod.h"

/**
* Takes as input a Data struct and implements a Solve() method returning the 2D or 1D Trapezoidal Rule
* approximation of the integral
* \brief Class implementing the Trapezoidal Rule approximation of integrals in 2D or 1D
*/

class TrapezoidalRule : public AbstractIntegrationMethod {
public:
      /** \brief Initialiser setting the data as a Data struct and also the function to integrate
  */
    TrapezoidalRule(Data data, Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXcd &coeff));
    /** \brief Method to compute approximate value of the 2D or 1D integral with Trapezoidal Rule
  */
  /**
  * Takes as input a Data struct and implements a Solve() method returning the 2D or 1D Trapezoidal Rule
  * approximation of the integral
   * \f{eqnarray*}{
     I \approx& \frac{h_x h_y}{4} \left[ f(x_0, y_0)+f(x_0,y_f)+f(x_f,y_0)+f(x_f,y_f) + 4 \sum_{i=1}^{n_y-1} \sum_{j=1}^{n_x-1} f(x_j, y_i) \right.\\
     & \left. + 2 \sum_{i=1}^{n_y-1} \left(f(x_0, y_i)+f(x_f,y_i)\right) + 2 \sum_{j=1}^{n_x-1} \left(f(x_j, y_0)+f(x_j,y_f)\right) \right]
    \f}
  */
 /*!
 \return The complex vector result of the integral approximation
 */
    Eigen::VectorXcd Solve();
};

#endif //TRAPEZOIDALRULE_H
