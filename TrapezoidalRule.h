//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef TRAPEZOIDALRULE_H
#define TRAPEZOIDALRULE_H

#include "AbstractIntegrationMethod.h"

class TrapezoidalRule : public AbstractIntegrationMethod {
public:
    TrapezoidalRule(Data data);
    Eigen::VectorXcd Solve();
};

#endif //TRAPEZOIDALRULE_H
