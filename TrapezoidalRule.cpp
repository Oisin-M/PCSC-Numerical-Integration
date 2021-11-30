//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#include "TrapezoidalRule.h"
#include "AbstractIntegrationMethod.h"

Eigen::VectorXcd TrapezoidalRule::Solve() {
    return data.f(data.boundsX(0,0), data.boundsY(0,0));
}

TrapezoidalRule::TrapezoidalRule(Data data) : AbstractIntegrationMethod(data) {}