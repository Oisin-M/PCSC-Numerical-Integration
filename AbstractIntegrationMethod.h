//
// Created by morrison@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef ABSTRACTINTEGRATIONMETHOD_H
#define ABSTRACTINTEGRATIONMETHOD_H


#include "DataStruct.h"

class AbstractIntegrationMethod {
public:
    // Constructor and destructor
    AbstractIntegrationMethod(Data data);
    virtual ~AbstractIntegrationMethod();
    
    virtual Eigen::VectorXcd Solve(Data data)=0;

protected:
    Data data;
};

#endif //ABSTRACTINTEGRATIONMETHOD_H
