//
// Created by morrison@INTRANET.EPFL.CH on 08.12.21.
//

#include <iostream>
#include <fstream>
#include "TxtReader.h"
#include "DataStruct.h"

Data TxtReader::OutputData() {
    int D;
    int m;
    int l;

    std::cout << fname << std::endl;

    std::ifstream file;

    try {
        file.open(fname);
        std::cout << "File opened successfully" << std::endl;
    }
    catch (std::ios_base::failure& e) {
        std::cerr << "File error: " << e.what() << std::endl;
        exit(1);
    }

    file >> D >> m >> l;

    Eigen::MatrixX2d boundsX(D,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY(D,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps(D,2); //X rows, 2 columns and ints
    Eigen::MatrixXcd coefficients(m,l); //X rows, 2 columns and ints

    for (int i=0; i<D; i++) {
        double x1, x2, y1, y2;
        int s1, s2;
        file >> x1 >> x2 >> y1 >> y2 >> s1 >> s2;
        boundsX(i, 0)=x1;
        boundsX(i, 1)=x2;
        boundsY(i, 0)=y1;
        boundsY(i, 1)=y2;
        noSteps(i,0)=s1;
        noSteps(i,1)=s2;
    }

    double re;
    double im;
    std::complex<double> z;
    for (int i=0; i<m; i++) {
        for (int j=0; j<l; j++) {
            file >> re >> im;
            z.real(re);
            z.imag(im);
            coefficients(i,j)=z;
        }
    }

    file.close();

    Data data = {.boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .coefficients=coefficients, .D=D, .m=m};
    return data;
}

TxtReader::TxtReader(std::string filename) : AbstractReader(filename) {}