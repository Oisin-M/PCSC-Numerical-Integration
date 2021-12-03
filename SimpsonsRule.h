//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
//

#ifndef SIMPSONSRULE_H
#define SIMPSONSRULE_H

#include "AbstractIntegrationMethod.h"

class SimpsonsRule : public AbstractIntegrationMethod {
public:
    SimpsonsRule(Data data);
    Eigen::VectorXcd Solve();
};

#endif //SIMPSONSRULE_H
