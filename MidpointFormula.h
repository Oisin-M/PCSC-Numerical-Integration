//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef MIDPOINTFORMULA_H
#define MIDPOINTFORMULA_H

#include "AbstractIntegrationMethod.h"

/**
* Takes as input a Data struct and implements a Solve() method returning the 2D or 1D Midpoint Formula
* approximation of the integral
* \brief Class implementing the Midpoint Formula approximation of integrals in 2D or 1D
*/

class MidpointFormula : public AbstractIntegrationMethod {
public:
  /** \brief Initialiser setting the data as a Data struct and also the function to integrate
  */
    MidpointFormula(Data &data, Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXcd &coeff));
 /** \brief Method to compute approximate value of the 2D or 1D integral with Midpoint Formula
  */
  /**
  * Takes as input a Data struct and implements a Solve() method returning the 2D or 1D Midpoint Formula
  * approximation of the integral
   * \f{eqnarray*}{
     I &\approx& h_x h_y \left[ \sum_{i=1}^{n_y} \sum_{j=1}^{n_x} f\left(\frac{x_{j-1}+x_j}{2}, \frac{y_{i-1}+y_i}{2}\right) \right]
    \f}
  */
 /*!
 \return The complex vector result of the integral approximation
 */
    Eigen::VectorXcd Solve();
};

#endif //MIDPOINTFORMULA_H
