//
// Created by morrison@INTRANET.EPFL.CH on 08.12.21.
//

#ifndef PROJECT5_TXTREADER_H
#define PROJECT5_TXTREADER_H

#include "DataStruct.h"
#include "AbstractReader.h"

class TxtReader : public AbstractReader {
public:
    TxtReader(std::string filename);
    Data OutputData();
    std::string ReadNthLine(const std::string& filename, int N);
    int countIntegers(std::string str);
    Eigen::VectorXd extractIntegers(std::string str);

};

#endif //PROJECT5_TXTREADER_H
