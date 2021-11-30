//
// Created by morrison@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef ABSTRACTINTEGRATIONMETHOD_H
#define ABSTRACTINTEGRATIONMETHOD_H

#include "DataStruct.h"

class AbstractIntegrationMethod {
public:
    AbstractIntegrationMethod(Data data);
    
    virtual Eigen::VectorXcd Solve()=0;

protected:
    Data data;
};

#endif //ABSTRACTINTEGRATIONMETHOD_H
