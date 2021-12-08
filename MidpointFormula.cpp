//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#include <iostream>
#include "MidpointFormula.h"
#include "AbstractIntegrationMethod.h"

Eigen::VectorXcd MidpointFormula::Solve() {

    Eigen::VectorXcd final_vec =  Eigen::VectorXcd::Zero(data.m);



    for(int d=0; d<data.D; ++d){
        Eigen::VectorXcd vec =  Eigen::VectorXcd::Zero(data.m);

        double x0=data.boundsX(d,0);
        double xf=data.boundsX(d,1);
        double y0=data.boundsY(d,0);
        double yf=data.boundsY(d,1);
        double hx = (xf-x0)/data.noSteps(d, 0);
        double hy = (yf-y0)/data.noSteps(d, 1);

        for (int i=1; i<=data.noSteps(d,1); ++i) {
            double yi=y0+i*hy;
            for (int j=1; j<=data.noSteps(d,0); ++j) {
                double xj=x0+j*hx;

                vec+=f((xj-hx+xj)/2, (yi-hy+yi)/2, data.coefficients);
            }
        }

        vec*=hx*hy;
        final_vec+=vec;
    }

    return final_vec;
}

MidpointFormula::MidpointFormula(Data data, Eigen::VectorXcd (*f)(double x, double y, Eigen::MatrixXcd coeff)) : AbstractIntegrationMethod(data, f) {}