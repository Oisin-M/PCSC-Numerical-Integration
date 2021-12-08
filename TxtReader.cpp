//
// Created by morrison@INTRANET.EPFL.CH on 08.12.21.
//

#include "TxtReader.h"
#include "DataStruct.h"

Data TxtReader::OutputData() {
    Eigen::MatrixX2d boundsX(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps(2,2); //X rows, 2 columns and ints
    Eigen::MatrixXd coefficents(2,2); //X rows, 2 columns and ints


    for (int i=0; i<2; i++) {
        boundsX(0,i)=i+1;
        boundsY(0,i)=i+1;
        noSteps(0,i)=i+1;
        coefficents(0,i)=i+1;
    }
    for (int i=0; i<2; i++) {
        boundsX(1,i)=i+1;
        boundsY(1,i)=i+1;
        noSteps(1,i)=i+1;
        coefficents(1,i)=i+1;
    }
    int D=2;
    int m=2;

    Data data = { .boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .coefficients=coefficents, .D=D, .m=m};
    return data;
}

TxtReader::TxtReader(std::string filename) : AbstractReader(filename) {}