//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#include <iostream>
#include "TrapezoidalRule.h"
#include "AbstractIntegrationMethod.h"

Eigen::VectorXcd TrapezoidalRule::Solve() {

    Eigen::VectorXcd final_vec =  Eigen::VectorXcd::Zero(data.m);

    for(int d=0; d<data.D; ++d){
        Eigen::VectorXcd vec =  Eigen::VectorXcd::Zero(data.m);

        double x0=data.boundsX(d,0);
        double xf=data.boundsX(d,1);
        double y0=data.boundsY(d,0);
        double yf=data.boundsY(d,1);
        double hx = (xf-x0)/data.noSteps(d, 0);
        double hy = (yf-y0)/data.noSteps(d, 1);

        vec += data.f(x0, y0);
        vec += data.f(x0, yf);
        vec += data.f(xf, y0);
        vec += data.f(xf, yf);

        for (int i=1; i<data.noSteps(d,1); ++i) {
            vec+= 2*data.f(x0, y0+i*hy);
            vec+= 2*data.f(xf, y0+i*hy);
            for (int j=1; j<data.noSteps(d,0); ++j) {
                vec+=4*data.f(x0+j*hx, y0+i*hy);
            }
        }

        for (int j=1; j<data.noSteps(d,0); ++j) {
            vec+= 2*data.f(x0+j*hx, y0);
            vec+= 2*data.f(xf+j*hx, yf);
        }

        vec*=hx*hy/4;
        final_vec+=vec;
    }

    return final_vec;
}

TrapezoidalRule::TrapezoidalRule(Data data) : AbstractIntegrationMethod(data) {}