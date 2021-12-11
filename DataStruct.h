//
// Created by morrison@INTRANET.EPFL.CH on 29.11.21.
//

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <Eigen/Dense>
#include <Eigen/Sparse>

/**
* \brief Struct storing data for the integral computation
*/

struct Data {
    /**
* \brief Matrix storing the bounds for the x-coordinate
*/
    Eigen::MatrixX2d boundsX; //X rows, 2 columns and doubles
    /**
* \brief Matrix storing the bounds for the y-coordinate
*/
    Eigen::MatrixX2d boundsY; //X rows, 2 columns and doubles
    /**
* \brief Matrix the number of steps to take in the approximation
*/
    Eigen::MatrixX2i noSteps; //X rows, 2 columns and ints
    /**
* \brief Matrix storing the polynomial coefficients specifying the function to integrate
*/
    Eigen::MatrixXcd coefficients; //store coefficients of polynomial
    /**
* \brief Integer storing the number of domains to integrate over
*/
    int D;
    /**
* \brief Integer storing the number of outputs of the function to integrate
*/
    int m;
};

#endif //DATASTRUCT_H
