//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#include <iostream>
#include "SimpsonsRule.h"
#include "AbstractIntegrationMethod.h"

Eigen::VectorXcd SimpsonsRule::Solve() {

    Eigen::VectorXcd final_vec =  Eigen::VectorXcd::Zero(data.m);

    for(int d=0; d<data.D; ++d){
        Eigen::VectorXcd vec = Eigen::VectorXcd::Zero(data.m);

        double x0=data.boundsX(d,0);
        double xf=data.boundsX(d,1);
        double y0=data.boundsY(d,0);
        double yf=data.boundsY(d,1);
        double hx = ((xf-x0)/data.noSteps(d, 0))/2;
        double hy = ((yf-y0)/data.noSteps(d, 1))/2;

        vec += data.f(x0, y0);
        vec += data.f(x0, yf);
        vec += data.f(xf, y0);
        vec += data.f(xf, yf);

        for (int i=1; i<=data.noSteps(d,1); ++i) {
            vec+=4*data.f(x0, y0+(2*i-1)*hy);
            vec+=4*data.f(xf, y0+(2*i-1)*hy);
            if (i!=data.noSteps(d,1)) {
                vec+=2*data.f(x0, y0+(2*i)*hy);
                vec+=2*data.f(xf, y0+(2*i)*hy);
            }

            for (int j=1; j<=data.noSteps(d,0); ++j) {
                vec+=16*data.f(x0+(2*j-1)*hx, y0+(2*i-1)*hy);
                if (i!=data.noSteps(d,1)) {
                    vec+=8*data.f(x0+(2*j-1)*hx, y0+(2*i)*hy);
                    if (j!=data.noSteps(d,0)) {
                        vec+=4*data.f(x0+(2*j)*hx, y0+(2*i)*hy);
                    }
                }
                if (j!=data.noSteps(d,0)) {
                    vec+=8*data.f(x0+(2*j)*hx, y0+(2*i-1)*hy);
                }
            }
        }

        for (int j=1; j<=data.noSteps(d,0); ++j) {
            vec+=4*data.f(x0+(2*j-1)*hx, y0);
            vec+=4*data.f(x0+(2*j-1)*hx, yf);
            if (j!=data.noSteps(d,0)) {
                vec+=2*data.f(x0+(2*j)*hx, y0);
                vec+=2*data.f(x0+(2*j)*hx, yf);
            }
        }

        vec*=hx*hy/9;
        final_vec+=vec;
    }

    return final_vec;
}

SimpsonsRule::SimpsonsRule(Data data) : AbstractIntegrationMethod(data) {}